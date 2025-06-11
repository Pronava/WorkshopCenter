<template>
  <div>
    <div ref="chart" style="width: 100%; height: 400px;"></div>
    <div style="margin-top: 10px; display: flex; gap: 10px;">

    <PlayAndCompare :audioData="audioFile" @startPlayback="handlePlaybackStart" />    
      
      <button @click="toggleStream">{{ isStreaming ? "Stop" : "Start" }} Realtime</button>
      <button @click="clearChart" style="margin-left: 10px;">Clear</button>
    </div>
  </div>
</template>

<script>
import { markRaw } from 'vue'; // 引入 markRaw
import * as echarts from 'echarts';
import PlayAndCompare from './PlayAndCompare.vue';

export default {
  name: 'LiveVisualizer',
  components: {
    PlayAndCompare,  // 注册组件
  },
  props: {
    originalPitches: {
      type: Array,
      default: () => [],
    },
    pointInterval: {
      type: Number,
      default: 0.05,
    },
    audioFile: {
    type: String,
    default: '',
  },
  },
  data() {
    return {
      isStreaming: false,
      ws: null,
      chart: null,
      pitchData: [],
      audioCtx: null,
      source: null,
      processor: null,
      stream: null,
      startTime: null,
      zoomStart: 0,  // 默认的 zoomStart
      zoomEnd: 30,   // 默认的 zoomEnd
    };
  },
  mounted() {
    this.chart = markRaw(echarts.init(this.$refs.chart));
    window.addEventListener('resize', this.resizeChart);
    this.renderChart();

    this.chart.on('datazoom', (event) => {
      if (event.batch && event.batch[0]) {
        this.zoomStart = event.batch[0].start;
        this.zoomEnd = event.batch[0].end;
      }
    });
  },
  beforeUnmount() {
    if (this.chart) this.chart.dispose();
    window.removeEventListener('resize', this.resizeChart);
    this.stopStream();
  },
  watch: {
    originalPitches() {
      this.renderChart();
    },
    pitchData() {
      this.renderChart();
    }
  },
  methods: {
    resizeChart() {
      if (this.chart) this.chart.resize();
    },
    renderChart() {
      if (!this.chart) return;

      const original = this.originalPitches || [];
      const live = this.pitchData || [];

      const maxLength = Math.max(original.length, live.length);
      const timeline = [];
      for (let i = 0; i < maxLength; i++) {
        timeline.push((i * this.pointInterval).toFixed(2));
      }

      // 修改后的频率到音阶的映射
      const freqToPitch = (freq) => {
        const pitchMapping = [
          { note: 'C', frequencies: [16.352, 32.703, 65.406, 130.81, 261.63, 523.25, 1046.5, 2093.0, 4186.0, 8372.0] },
          { note: 'C#', frequencies: [17.324, 34.648, 69.296, 138.59, 277.18, 554.37, 1108.7, 2217.5, 4434.9, 8869.8] },
          { note: 'D', frequencies: [18.354, 36.708, 73.416, 146.83, 293.66, 587.33, 1174.7, 2349.3, 4698.6, 9397.3] },
          { note: 'D#', frequencies: [19.445, 38.891, 77.782, 155.56, 311.13, 622.25, 1244.5, 2489.0, 4978.0, 9956.1] },
          { note: 'E', frequencies: [20.602, 41.203, 82.407, 164.81, 329.63, 659.26, 1318.5, 2637.0, 5274.0, 10548] },
          { note: 'F', frequencies: [21.827, 43.654, 87.307, 174.61, 349.23, 698.46, 1396.9, 2793.8, 5587.7, 11175] },
          { note: 'F#', frequencies: [23.125, 46.249, 92.499, 185.00, 369.99, 739.99, 1480.0, 2960.0, 5919.9, 11840] },
          { note: 'G', frequencies: [24.500, 48.999, 97.999, 196.00, 392.00, 783.99, 1568.0, 3136.0, 6271.9, 12544] },
          { note: 'G#', frequencies: [25.957, 51.913, 103.83, 207.65, 415.30, 830.61, 1661.2, 3322.4, 6644.9, 13290] },
          { note: 'A', frequencies: [27.500, 55.000, 110.00, 220.00, 440.00, 880.00, 1760.0, 3520.0, 7040.0, 14080] },
          { note: 'A#', frequencies: [29.135, 58.270, 116.54, 233.08, 466.16, 932.33, 1864.7, 3729.3, 7458.6, 14917] },
          { note: 'B', frequencies: [30.868, 61.735, 123.47, 246.94, 493.88, 987.77, 1975.5, 3951.1, 7902.1, 15804] },
        ];

        let octave = 0;
        let note = '';
        let minDiff = Infinity;

        pitchMapping.forEach(({ note: currentNote, frequencies }) => {
          frequencies.forEach((f, index) => {
            const diff = Math.abs(freq - f);
            if (diff < minDiff) {
              minDiff = diff;
              note = currentNote;
              octave = index;
            }
          });
        });

        return `${note}${octave}`;
      };

      const option = {
        title: { text: `音高曲线 (总时长约 ${(maxLength * this.pointInterval).toFixed(1)} 秒)` },
        tooltip: {
          trigger: 'axis',
          formatter: (params) => {
            let frequency = null;
            let pitch = '';
            let seriesName = '';

            params.forEach(param => {
              const { seriesIndex, data } = param;
              frequency = data; // 频率
              pitch = freqToPitch(frequency); // 音阶

              if (seriesIndex === 0) {
                seriesName = '后端原曲';
              } else if (seriesIndex === 1) {
                seriesName = '实时音高';
              }
            });

            return `时间: ${params[0].axisValue}秒<br/>${seriesName} 频率: ${frequency.toFixed(2)} Hz<br/>${seriesName} 音阶: ${pitch}`;
          },
        },
        xAxis: {
          type: 'category',
          name: '时间（秒）',
          data: timeline,
          axisLabel: { rotate: 45 },
          boundaryGap: false,
        },
        yAxis: {
          type: 'value',
          name: '频率（Hz）',
        },
        dataZoom: [
          {
            type: 'slider',
            start: this.zoomStart,
            end: this.zoomEnd,
            handleSize: 8,
            handleStyle: { color: '#aaa' },
            bottom: 10,
            realtime: true,
          },
          { type: 'inside' },
        ],
        series: [
          {
            name: '后端原曲',
            type: 'line',
            data: original,
            smooth: true,
            lineStyle: { color: '#5470C6' },
            connectNulls: true,
          },
          {
            name: '实时音高',
            type: 'line',
            data: live,
            smooth: true,
            lineStyle: { color: '#EE6666' },
            connectNulls: true,
          },
        ],
      };

      this.chart.setOption(option);
      this.restoreZoom();
    },
    restoreZoom() {
      if (this.chart && this.zoomStart !== undefined && this.zoomEnd !== undefined) {
        this.chart.dispatchAction({
          type: 'dataZoom',
          start: this.zoomStart,
          end: this.zoomEnd,
        });
      }
    },
    async toggleStream() {
      if (this.isStreaming) {
        await this.stopStream();
      } else {
        await this.startStream();
      }
    },
    async startStream() {
      this.isStreaming = true;
      if (!this.startTime) {
        this.startTime = Date.now();
      }

      this.ws = new WebSocket('ws://localhost:8000/ws/audio-stream');
      this.ws.binaryType = 'arraybuffer';

      this.ws.onopen = async () => {
        try {
          this.stream = await navigator.mediaDevices.getUserMedia({ audio: true });
          this.audioCtx = new AudioContext();
          this.source = this.audioCtx.createMediaStreamSource(this.stream);
          this.processor = this.audioCtx.createScriptProcessor(4096, 1, 1);

          this.processor.onaudioprocess = (e) => {
            const input = e.inputBuffer.getChannelData(0);
            const pcm = new Int16Array(input.length);
            for (let i = 0; i < input.length; i++) {
              pcm[i] = input[i] * 32767;
            }
            if (this.ws && this.ws.readyState === WebSocket.OPEN) {
              this.ws.send(pcm.buffer);
            }
          };

          this.source.connect(this.processor);
          this.processor.connect(this.audioCtx.destination);
        } catch (err) {
          console.error("获取音频流失败:", err);
          this.isStreaming = false;
        }
      };

      this.ws.onmessage = (event) => {
        try {
          const data = JSON.parse(event.data);
          const pitches = data.pitches || [];
          this.pitchData.push(...pitches);
          this.renderChart();
        } catch (e) {
          console.error('解析数据错误：', e);
        }
      };

      this.ws.onclose = () => {
        this.isStreaming = false;
      };

      this.ws.onerror = (err) => {
        console.error('WebSocket 错误：', err);
        this.isStreaming = false;
      };
    },
    async stopStream() {
      this.isStreaming = false;
      if (this.processor) {
        this.processor.disconnect();
        this.processor.onaudioprocess = null;
      }
      if (this.source) this.source.disconnect();
      if (this.audioCtx) await this.audioCtx.close();
      if (this.stream) this.stream.getTracks().forEach(track => track.stop());
      if (this.ws && (this.ws.readyState === WebSocket.OPEN || this.ws.readyState === WebSocket.CONNECTING)) this.ws.close();

      this.ws = null;
      this.audioCtx = null;
      this.source = null;
      this.processor = null;
      this.stream = null;

      console.log("已停止音频采集与WebSocket连接");
    },
    clearChart() {
      this.pitchData = [];
      this.startTime = null;
      if (this.chart) this.chart.clear();
      this.renderChart();
    },
  },
};
</script>

<style scoped>
div[ref="chart"] {
  width: 100%;
  height: 400px;
}
button {
  cursor: pointer;
}
</style>
