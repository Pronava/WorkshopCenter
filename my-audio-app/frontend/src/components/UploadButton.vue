<template>
  <div class="upload-container">
    <!-- 选择文件按钮 -->
    <input 
      type="file" 
      ref="fileInput" 
      @change="handleFileChange" 
      style="display: none" 
    />
    <button @click="triggerFileInput">选择文件</button>

    <!-- 提交文件按钮 -->
    <button 
      :disabled="!file" 
      @click="submitFile" 
    >
      提交文件
    </button>

    <!-- 显示已选择的文件名 -->
    <div v-if="file">
      <p>已选择文件: {{ file.name }}</p>
    </div>
  </div>
</template>

<script>
export default {
  data() {
    return {
      file: null, // 存储选择的文件
    };
  },
  methods: {
    // 激活文件选择器
    triggerFileInput() {
      this.$refs.fileInput.click(); // 模拟点击文件选择器
    },

    // 处理文件选择
    handleFileChange(event) {
      const selectedFile = event.target.files[0]; // 获取选择的文件
      if (selectedFile) {
        this.file = selectedFile; // 存储文件
      }
    },

    // 提交文件到后端
    async submitFile() {
      if (this.file) {
        const formData = new FormData();
        formData.append('file', this.file);

        try {
          // 模拟将文件提交到后端的 API 接口
          const response = await fetch('http://127.0.0.1:8000/upload/', {
            method: 'POST',
            body: formData,
          });

          if (response.ok) {
            const data = await response.json(); // 解析响应
            console.log('文件上传成功:', data);
            alert('文件上传成功！');
          } else {
            const errorData = await response.text(); // 获取错误响应内容
            console.error('上传失败:', errorData);
            alert('文件上传失败，请重试！');
          }
        } catch (error) {
          console.error('上传失败:', error);
          alert('上传过程中出现错误！');
        }
      }
    },
  },
};
</script>

<style scoped>
.upload-container {
  display: flex;
  flex-direction: row; /* 横向排列 */
  justify-content: center; /* 水平居中 */
  align-items: center; /* 垂直居中 */
  gap: 20px; /* 按钮之间的间距 */
  padding-top: 10px;
}

button {
  padding: 10px 20px;
  font-size: 16px;
  cursor: pointer;
}

button:disabled {
  background-color: #ccc;
  cursor: not-allowed;
}

p {
  margin-top: 10px;
}
</style>
