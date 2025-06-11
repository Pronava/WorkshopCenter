from fastapi import APIRouter, File, UploadFile
from app.services.audio_service import save_audio_file

router = APIRouter()

@router.post("/")
async def upload_audio(file: UploadFile = File(...)):
    # 设置保存路径
    file_location = f"audio_files/{file.filename}"
    
    # 保存音频文件
    saved_file_path = save_audio_file(file, file_location)
    
    # 返回上传成功的消息和文件位置
    return {
        "message": "File uploaded successfully",
        "file_location": saved_file_path
    }
