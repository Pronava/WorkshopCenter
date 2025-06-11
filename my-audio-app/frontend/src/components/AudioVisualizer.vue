<template>
  <LiveVisualizer />
</template>

<script>
import * as echarts from 'echarts';
import LiveVisualizer from './LiveVisualizer.vue';

export default {
  components: {
    LiveVisualizer
  },
  name: 'AudioVisualizer',
  props: {
    audioData: {
      type: Object,
      default: null,
    },
  },
  watch: {
    audioData: {
      immediate: true,
      handler(newVal) {
        console.log('🎵 收到的新 audioData：', newVal);

        if (
          newVal?.timeline?.length > 0 &&
          newVal?.hop_length &&
          newVal?.sr
        ) {
          console.log('✅ 将要绘制的 timeline 数组：', newVal.timeline);
          this.renderChart(newVal.timeline, newVal.hop_length, newVal.sr);
        } else {
          console.warn('⚠️ timeline 无数据或参数不足，清除图表');
          this.clearChart();
        }
      },
    },
  },
  mounted() {
    this.chart = echarts.init(this.$refs.chart);
    window.addEventListener('resize', this.resizeChart);
  },
  beforeUnmount() {
    if (this.chart) {
      this.chart.dispose();
    }
    window.removeEventListener('resize', this.resizeChart);
  },
  methods: {
    resizeChart() {
      if (this.chart) {
        this.chart.resize();
      }
    },
    freqToNoteName(freq) {
      if (!freq || freq < 20) return ''; // 忽略无效频率
      const A4 = 440;
      const noteNames = ['C', 'C#', 'D', 'D#', 'E', 'F', 'F#', 'G', 'G#', 'A', 'A#', 'B'];
      const semitone = Math.round(12 * Math.log2(freq / A4));
      const noteIndex = (semitone + 9 + 1200) % 12; // 保证 index 为正
      const octave = 4 + Math.floor((semitone + 9) / 12);
      return noteNames[noteIndex] + octave;
    },
    renderChart(pitchData, hopLength, sr) {
      const timeAxis = pitchData.map((_, i) => (i * hopLength / sr).toFixed(2));
      const noteData = pitchData.map(freq => this.freqToNoteName(freq));

      // 获取唯一音高并排序（按音高）
      const uniqueNotes = Array.from(new Set(noteData)).filter(n => n).sort((a, b) => {
        const parse = note => {
          const match = note.match(/([A-G]#?)(\d)/);
          const order = ['C', 'C#', 'D', 'D#', 'E', 'F', 'F#', 'G', 'G#', 'A', 'A#', 'B'];
          if (!match) return -1;
          return parseInt(match[2]) * 12 + order.indexOf(match[1]);
        };
        return parse(a) - parse(b);
      });

      const option = {
        title: {
          text: '音高曲线图（音名 vs 时间）',
        },
        tooltip: {
          trigger: 'axis',
        },
        xAxis: {
          type: 'category',
          name: '时间 (秒)',
          data: timeAxis,
          axisLabel: {
            interval: Math.floor(timeAxis.length / 10), // 自动间隔标签
            rotate: 45
          }
        },
        yAxis: {
          type: 'category',
          name: '音高',
          data: uniqueNotes,
        },
        series: [
          {
            name: '音高',
            type: 'line',
            data: noteData,
            smooth: true,
            symbol: 'circle',
            lineStyle: {
              color: '#3f51b5',
              width: 2,
            },
            areaStyle: {
              color: 'rgba(63, 81, 181, 0.1)',
            },
          },
        ],
      };
      this.chart.setOption(option);
    },
    clearChart() {
      if (this.chart) {
        this.chart.clear();
      }
    },
  },
};
</script>

<style scoped>
/* 让图表容器填满父元素 */
:host, div[ref="chart"] {
  width: 100%;
  height: 100%;
}
</style>
