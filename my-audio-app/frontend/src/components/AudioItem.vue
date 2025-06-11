<template>
  <div 
    class="audio-item" 
    :class="{ selected: selected }" 
    @click="selectAudio">
    <span>{{ audioFile }}</span>
  </div>
</template>

<script>
export default {
  props: {
    audioFile: String,  // 音频文件名
    selected: Boolean,  // 是否选中
  },
  methods: {
    selectAudio() {
      this.$emit("select-audio", this.audioFile);  // 触发事件，返回选中的音频
    },
  },
};
</script>

<style scoped>
.audio-item {
  cursor: pointer;
  padding: 10px;
  margin: 5px 0;
  background-color: #f1f1f1;
  border-radius: 5px;
  text-align: center;
  transition: background-color 0.3s ease; /* 平滑的背景过渡 */
}

.audio-item:hover {
  background-color: #ddd;
}

.audio-item.selected {
  background-color: #3f51b5;  /* 选中时的背景色 */
  color: white;  /* 选中时的文字颜色 */
}
</style>
