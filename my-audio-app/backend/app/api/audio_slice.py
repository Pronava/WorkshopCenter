from fastapi import APIRouter
from fastapi.responses import FileResponse
import os
import librosa
import soundfile as sf

router = APIRouter()

@router.get("/slice-audio")
def slice_audio(filename: str, start: float = 0, end: float = 5):
    path = f"./audio_files/{filename}"
    print(f"[slice_audio] 请求参数 - filename: {filename}, start: {start}, end: {end}")
    print(f"[slice_audio] 计算文件路径: {path}")
    
    if not os.path.exists(path):
        print(f"[slice_audio] 文件不存在: {path}")
        return {"error": "File not found"}

    y, sr = librosa.load(path, offset=start, duration=end-start)
    os.makedirs('./temp', exist_ok=True)
    slice_path = f"./temp/{filename}_slice.wav"
    sf.write(slice_path, y, sr)

    print(f"[slice_audio] 切片音频生成路径: {slice_path}")

    return FileResponse(slice_path, media_type="audio/wav", filename=f"{filename}_slice.wav")
