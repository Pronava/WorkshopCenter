<template> 
  <div class="player-container">
    <!-- 播放/暂停按钮 -->
    <button @click="togglePlayback" class="play-button">
      <i v-if="isPlaying" class="fas fa-pause"></i>
      <i v-else class="fas fa-play"></i>
      {{ isPlaying ? '暂停' : '播放' }}
    </button>
    
    <!-- 可拖动的进度条 -->
    <div class="progress-container">
      <input 
        type="range" 
        v-bind="progressRangeProps" 
        @input="updateProgress"
        class="progress-bar" 
        ref="progressBar"
      />
      <span class="time-display">{{ currentTime }} / {{ duration }}</span>
    </div>

    <!-- 动态频谱图 -->
    <div class="waveform-container">
      <canvas ref="canvas" width="500" height="150"></canvas>
    </div>
  </div>
</template>

<script>
export default {
  props: {
    audioData: String,  // 接收父组件传来的音频文件名
  },
  data() {
    return {
      audio: null,          // Audio 实例
      audioContext: null,   // Web Audio Context
      analyser: null,       // AnalyserNode
      isPlaying: false,     // 控制播放/暂停状态
      currentTime: 0,       // 当前播放时间
      duration: 0,          // 音频总时长
      progress: 0,          // 进度条进度
    };
  },
  computed: {
    progressRangeProps() {
      return {
        min: 0,
        max: this.duration,
        value: this.currentTime,
      };
    }
  },
  watch: {
    // 监听 audioData prop 变化
    audioData(newVal, oldVal) {
      if (newVal !== oldVal) {
        // 如果音频文件变化，停止当前音频并开始播放新音频
        this.stopPlayback();
        this.startPlayback();
      }
    }
  },
  methods: {
    // 切换播放/暂停
    togglePlayback() {
      if (this.audio) {
        if (this.isPlaying) {
          this.audio.pause();
        } else {
          this.audio.play();
        }
        this.isPlaying = !this.isPlaying;
      } else {
        this.startPlayback();
      }
    },

    // 开始播放音频
    async startPlayback() {
      try {
        const start = 0;
        const end = 300;
        const url = `http://127.0.0.1:8000/slice-audio?filename=${encodeURIComponent(this.audioData)}&start=${start}&end=${end}`;
        
        const response = await fetch(url);
        const blob = await response.blob();
        this.audio = new Audio(URL.createObjectURL(blob));

        // 确保音频的元数据加载完成后再获取音频时长
        this.audio.onloadedmetadata = () => {
          this.duration = this.audio.duration;
          console.log('音频时长:', this.duration);  // 确保时长有效
        };

        this.audioContext = new (window.AudioContext || window.webkitAudioContext)();
        this.analyser = this.audioContext.createAnalyser();
        const source = this.audioContext.createMediaElementSource(this.audio);
        source.connect(this.analyser);
        this.analyser.connect(this.audioContext.destination);

        // 等待音频元数据加载完成后再开始播放
        this.audio.play();
        this.isPlaying = true;

        this.audio.ontimeupdate = this.updateTime;
        this.audio.onended = this.handlePlaybackEnd;

        this.updateFrequencyData();
      } catch (err) {
        console.error("播放失败：", err);
      }
    },

    // 停止当前播放
    stopPlayback() {
      if (this.audio) {
        this.audio.pause();
        this.audio.currentTime = 0;
        this.isPlaying = false;
      }
    },

    // 更新进度条
    updateTime() {
      // 检查 this.audio.currentTime 和 this.duration 是否为有效值
      if (isNaN(this.currentTime) || isNaN(this.duration)) {
        console.error('无效的时间值:', this.currentTime, this.duration);
        return; // 如果无效，退出函数
      }

      this.currentTime = this.audio.currentTime;
      this.progress = (this.currentTime / this.duration) * 100;

      // 更新进度条的背景色和宽度
      this.$nextTick(() => {
        const progressBar = this.$refs.progressBar;
        const progress = this.progress;

        // 设置进度条的遮罩宽度
        progressBar.style.setProperty('--progress', `${progress}%`);

        // 打印当前进度宽度
        console.log('当前进度宽度：', progress, '%');
      });
    },

    // 更新播放进度
    updateProgress(event) {
      const value = event.target.value;
      this.audio.currentTime = value;
      this.currentTime = value;
    },

    // 频谱数据更新
    updateFrequencyData() {
      const canvas = this.$refs.canvas;
      const ctx = canvas.getContext('2d');
      const bufferLength = this.analyser.frequencyBinCount;
      const dataArray = new Uint8Array(bufferLength);

      const draw = () => {
        requestAnimationFrame(draw);
        this.analyser.getByteFrequencyData(dataArray);
        ctx.clearRect(0, 0, canvas.width, canvas.height);

        const barWidth = (canvas.width / bufferLength) * 2.5;
        let x = 0;

        for (let i = 0; i < bufferLength; i++) {
          const barHeight = dataArray[i];
          const r = barHeight + 100;
          const g = 50;
          const b = 50;
          ctx.fillStyle = `rgb(${r}, ${g}, ${b})`;
          ctx.fillRect(x, canvas.height - barHeight, barWidth, barHeight);
          x += barWidth + 1;
        }
      };

      draw();
    },

    // 播放结束后的处理
    handlePlaybackEnd() {
      this.isPlaying = false;
    },
  },
};
</script>

<style scoped>
/* 整个播放器容器样式 */
.player-container {
  max-width: 600px;
  min-width: 600px;
  margin: 0 auto;
  padding: 15px;
  background-color: #1a1a1a;
  border-radius: 10px;
  color: #fff;
  box-shadow: 0 0 15px rgba(0, 0, 0, 0.2);
  text-align: center;
}

/* 播放按钮样式 */
.play-button {
  background-color: #4CAF50;
  color: white;
  font-size: 18px;
  border: none;
  border-radius: 5px;
  padding: 12px 20px;
  cursor: pointer;
  display: flex;
  align-items: center;
  justify-content: center;
  transition: background-color 0.3s ease;
  margin-bottom: 15px;
}

.play-button:hover {
  background-color: #45a049;
}

/* 进度条容器 */
.progress-container {
  margin-top: 20px; 
  display: flex;
  flex-direction: column;
  align-items: center;
}

/* 进度条 */
.progress-bar {
  width: 450px;
  height: 10px;
  max-width: 450px;
  min-width: 450px;
  background: #ff7f00; /* 默认的橙色背景 */
  border-radius: 5px;
  outline: none;
  appearance: none;
  cursor: pointer;
  transition: background 0.2s ease-in-out;
  position: relative;
}

/* 为进度条添加动态遮罩 */
.progress-bar::before {
  content: '';
  position: absolute;
  top: 0;
  left: 0;
  height: 100%;
  background-color: #f5ebeb; /* 播放部分的颜色 */
  border-radius: 5px;
  z-index: 10;
  width: var(--progress, 0%); /* 动态宽度 */
}

/* 滑块样式 */
.progress-bar::-webkit-slider-thumb {
  width: 15px;
  height: 10px;
  background: #8B0000; /* 深红色滑块 */
  border-radius: 30%;
  cursor: pointer;
  border: none;
  appearance: none;
  position: relative;
  z-index: 2;
  opacity: 0; /* 隐藏滑块 */
}

/* 进度条上的时间显示 */
.time-display {
  margin-top: 10px;
  color: #bbb;
  font-size: 14px;
}

/* 频谱图容器 */
.waveform-container {
  margin-top: 20px;
  background-color: #222;
  border-radius: 10px;
}

/* Canvas样式 */
canvas {
  width: 100%;
  height: auto;
  border-radius: 10px;
}
</style>
