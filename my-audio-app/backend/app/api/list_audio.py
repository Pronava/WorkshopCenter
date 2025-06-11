# backend/app/api/list_audio.py
from fastapi import APIRouter
import os

router = APIRouter()

@router.get("/list")
async def get_audio_list():
    audio_dir = 'audio_files'
    audio_files = []

    if os.path.exists(audio_dir):
        audio_files = [file for file in os.listdir(audio_dir) if file.endswith(('.mp3', '.wav'))]
    
    return {"audio_files": audio_files}
