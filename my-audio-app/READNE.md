脚手架初始化项目

技术栈：前端vue加后端python fastapi，前后端分离

启动后端：
uvicorn main:app --reload
启动前端：
npm run serve

my-audio-app/
├── backend/
│   ├── app/
│   │   ├── __init__.py
│   │   ├── models.py                # 数据模型
│   │   ├── utils.py                 # 音频处理工具
│   │   ├── services/
│   │   │   ├── audio_service.py     # 音频解析和分析逻辑
│   │   └── api/
│   │       ├── __init__.py
│   │       ├── upload.py            # 文件上传接口
│   │       ├── analyze.py           # 音频分析接口
│   │       ├── audio_slice.py
│   │       ├── compare.py
│   │       ├── list_audio.py        # 获取音频列表接口
│   ├── requirements.txt             # 项目依赖
│   ├── Dockerfile                   # Docker 配置（可选）
│   └── main.py                      # FastAPI 应用入口
└── frontend/
    ├── public/
    │   ├── index.html
    ├── src/
    │   ├── assets/
    │   ├── components/
    │   │   ├── Sidebar.vue          # 左侧边栏
    │   │   ├── AudioVisualizer.vue  # 音频可视化区域
    │   │   ├── UploadButton.vue     # 上传按钮组件
    │   │   ├── PlayAndCommpare.vue    
    │   │   ├── AudioItem.vue        # 每个音频文件的显示项（用于侧边栏）
    │   ├── store/
    │   │   └── audio.js             # Vuex store 管理音频数据
    │   ├── router/
    │   │   └── index.js             # 路由配置
    │   └── App.js                   # 路由配置   
    ├── package.json
    ├── vue.config.js                # Vue 配置
    └── Dockerfile                   # Docker 配置（可选）
<template>
  <div ref="chart" style="width: 100%; height: 100%"></div>
  <LiveVisualizer />
</template>

<script>
