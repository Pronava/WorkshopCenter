<style>
  .grid-container {
    display: grid;
    grid-template-columns: repeat(auto-fill, minmax(280px, 1fr));
    gap: 15px;
    justify-items: center;
    margin-top: 10px;
  }

  .grid-container img {
    width: 280px;
    height: 180px;
    object-fit: cover;
    border-radius: 8px;
    box-shadow: 0 4px 10px rgba(0,0,0,0.1);
    transition: transform 0.25s ease;
    cursor: pointer;
  }

  .grid-container img:hover {
    transform: scale(1.05);
    box-shadow: 0 8px 16px rgba(0,0,0,0.2);
  }

  @media (max-width: 768px) {
    .grid-container {
      grid-template-columns: repeat(auto-fill, minmax(150px, 1fr));
    }
    .grid-container img {
      width: 150px;
      height: 100px;
    }
  }
</style>

# 🚀 WorkshopCenter 项目总览

> 📌 **说明：不定期更新**

---

## 💎 饰品交易平台

- **技术栈**：HTML, CSS, JavaScript, jQuery, Ajax, MySQL  

**示意图：**  
<div class="grid-container">
  <img src="饰品交易/相关图片/admin.png" alt="饰品交易示意图1" />
  <img src="饰品交易/相关图片/hp.png" alt="饰品交易示意图2" />
  <img src="饰品交易/相关图片/er.png" alt="饰品交易示意图3" />
</div>

---

## 🔍 llm_code

- **技术栈**：Python, Flask, MySQL  

**示意图：**  
<div class="grid-container">
  <img src="llm_code/image/1.png" alt="llm_code示意图1" />
  <img src="llm_code/image/2.png" alt="llm_code示意图2" />
  <img src="llm_code/image/3.png" alt="llm_code示意图3" />
  <img src="llm_code/image/4.png" alt="llm_code示意图4" />
  <img src="llm_code/image/5.png" alt="llm_code示意图5" />
  <img src="llm_code/image/6.png" alt="llm_code示意图6" />
</div>

---

## 🧠 NextJs_Workshop

- **技术栈**：JavaScript, Next.js, React, Node.js, MySQL, Express

**示意图：**  
<div class="grid-container">
  <img src="NextJs_Workshop/image/1.png" alt="NextJs_Workshop示意图1" />
  <img src="NextJs_Workshop/image/3.png" alt="NextJs_Workshop示意图2" />
  <img src="NextJs_Workshop/image/2.png" alt="NextJs_Workshop示意图3" />
  <img src="NextJs_Workshop/image/4.png" alt="NextJs_Workshop示意图4" />
  <img src="NextJs_Workshop/image/5.png" alt="NextJs_Workshop示意图5" />
</div>

---

## 🎧 MyAudioApp

- **技术栈**：JavaScript, Web Audio API, Vue.js, FastAPI  

- **核心功能：**
  - 音频切片上传与播放  
  - 实时人声音高与原曲比对反馈  
  - 波形图与音高走势的动态可视化

**示意图：**  
<div class="grid-container">
  <img src="my-audio-app/imag/1.png" alt="MyAudioApp示意图1" />
  <img src="my-audio-app/imag/2.png" alt="MyAudioApp示意图2" />
  <img src="my-audio-app/imag/3.png" alt="MyAudioApp示意图3" />
  <img src="my-audio-app/imag/4.png" alt="MyAudioApp示意图4" />
  <img src="my-audio-app/imag/5.png" alt="MyAudioApp示意图5" />
  <img src="my-audio-app/imag/6.png" alt="MyAudioApp示意图6" />
</div>

---

## 📱 MobileComputing

- **技术栈**：C++, Qt, WebSocket, MySQL  
- **简介**：使用 Qt 编写的本地聊天应用，结合 WebSocket 实现局域网实时通信与数据库记录功能。
