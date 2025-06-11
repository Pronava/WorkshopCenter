<template>
  <div class="sidebar">
    <h3>Uploaded Audios</h3>
    <div v-for="audio in audioList" :key="audio">
      <AudioItem 
        :audioFile="audio" 
        :selected="audio === selectedAudioFile"
        @select-audio="selectAudio" 
      />
    </div>
  </div>
</template>

<script>
import AudioItem from './AudioItem.vue';

export default {
  props: {
    audioList: Array,
    selectedAudioFile: String,  // 从父组件传递的选中的音频文件名
  },
  components: {
    AudioItem,
  },
  methods: {
    selectAudio(audioFile) {
      this.$emit('selectAudio', audioFile);  // 触发父组件的方法
    },
  },
};
</script>

<style scoped>
.sidebar {
  width: 250px;
  padding: 10px;
  background-color: #f4f4f4;
  height: 100%;
}
</style>
