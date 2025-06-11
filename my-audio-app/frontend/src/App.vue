<template>
  <div id="app">
    <div class="header">
      <UploadButton @upload="handleUpload" />
    </div>

    <div class="main-content">
      <Sidebar 
        :audioList="audioList" 
        :selectedAudioFile="selectedAudioFile" 
        @selectAudio="handleSelectAudio" 
      />
      <div class="audio-visualizer">
        <!-- 如果没有选中音频文件，则显示占位文字 -->
        <div v-if="!selectedAudioFile" class="placeholder">
          <p>🎶 欢迎来到音频分析工具！🎧</p>
          <p>请上传或选择一个音频文件进行分析。</p>
        </div>
        <!-- 如果选中音频文件，则显示音高可视化 -->
        <LiveVisualizer
          v-if="selectedAudio && selectedAudio.timeline && selectedAudio.name"
          :originalPitches="selectedAudio.timeline"
          :pointInterval="0.05"
          :windowDuration="10"
          :isRecording="isRecording"
          :audioFile="selectedAudio.name"
        />
      </div>
    </div>
  </div>
</template>

<script>
import UploadButton from './components/UploadButton.vue';
import Sidebar from './components/Sidebar.vue';
import LiveVisualizer from './components/LiveVisualizer.vue';

export default {
  name: 'App',
  components: {
    UploadButton,
    Sidebar,
    LiveVisualizer,
  },
  data() {
    return {
      audioList: [], // 音频文件列表
      selectedAudio: { timeline: [] }, // 当前选中的音频数据
      isRecording: false, // 是否正在录音
      selectedAudioFile: '', // 当前选中的音频文件名
    };
  },
  mounted() {
    this.fetchAudioList();  // 获取音频列表
  },
  methods: {
    // 获取音频文件列表
    async fetchAudioList() {
      try {
        const response = await fetch('http://127.0.0.1:8000/audio/list');
        if (!response.ok) throw new Error('网络错误，状态码：' + response.status);
        const data = await response.json();
        this.audioList = data.audio_files;
      } catch (error) {
        console.error('获取音频列表失败:', error);
      }
    },

    handleUpload() {
      this.fetchAudioList();  // 重新获取音频列表
    },

    // 选择音频文件
    async handleSelectAudio(audioFile) {
      try {
        const start = 0;
        const end = 60;
        const response = await fetch(`http://127.0.0.1:8000/analyze/pitch?filename=${encodeURIComponent(audioFile)}&start=${start}&end=${end}`);
        if (!response.ok) throw new Error(`HTTP error! status: ${response.status}`);
        const data = await response.json();

        const mainPitches = data.main_pitches || [];
        const sr = data.sr || 22050;
        const hopLength = data.hop_length || 512;

        this.selectedAudio = {
          name: audioFile, // 存储选中的音频文件名
          timeline: mainPitches,
          sr,
          hop_length: hopLength
        };

        this.selectedAudioFile = audioFile;  // 更新选中的音频文件
      } catch (error) {
        console.error('音频分析失败:', error);
        this.selectedAudio = null;
      }
    },

    toggleRecording() {
      this.isRecording = !this.isRecording;
    },

    stopRecording() {
      this.isRecording = false;
    },
  },
};
</script>

<style scoped>
/* App Container */
html, body, #app {
  font-family: 'Arial', sans-serif;
  display: flex;
  flex-direction: column;
  background-color: #f4f7fc;
  height: 100%;
  width: 100%;
  margin: 0;
  padding: 0;
}

/* Header */
.header {
  padding: 20px;
  width: 100%;
  background-color: #3f51b5;
  color: white;
  text-align: center;
}

/* Main Content */
.main-content {
  width: 100%;
  height: 100%;
  display: flex;
  flex: 1;
  padding: 20px;
  gap: 20px;
}

/* Audio Visualizer */
.audio-visualizer {
  flex: 3;
  height: 100%;
  width: 100%;
  background-color: white;
  border-radius: 10px;
  box-shadow: 0 2px 4px rgba(0,0,0,0.1);
  padding: 20px;
  overflow: hidden;
  min-height: 0;
  display: flex;
  flex-direction: column;
  position: relative;  /* Added to ensure child elements fill remaining space */
}

/* Placeholder */
.audio-visualizer > .placeholder {
  display: flex;
  justify-content: center;
  align-items: center;
  height: 700px;   /* Ensures placeholder takes up the full height */
  width: 100%;    /* Ensure full width */
  text-align: center;
  color: #aaa;
  font-size: 24px;
  flex-direction: column;
}

.audio-visualizer > .placeholder p {
  margin: 10px;
  font-size: 18px;
  color: #3f51b5;
}

</style>
