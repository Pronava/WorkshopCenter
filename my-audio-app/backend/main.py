from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware
from app.api import upload, analyze, list_audio
from app.api import audio_slice
from app.api import compare
from app.api import ws_audio

# 创建 FastAPI 实例
app = FastAPI()

# 配置 CORS 中间件
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],  # 允许来自此域名的请求
    allow_credentials=True,
    allow_methods=["*"],  # 允许所有 HTTP 方法
    allow_headers=["*"],  # 允许所有请求头
)

# 引入并注册路由
app.include_router(upload.router, prefix="/upload", tags=["upload"])
app.include_router(analyze.router, prefix="/analyze", tags=["analyze"])
app.include_router(list_audio.router, prefix="/audio", tags=["audio"])
app.include_router(audio_slice.router)
app.include_router(compare.router)
app.include_router(ws_audio.router)

