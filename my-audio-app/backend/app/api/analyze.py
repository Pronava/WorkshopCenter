from fastapi import APIRouter, HTTPException
from app.services.audio_service import analyze_pitch
import os
import traceback
from fastapi.responses import JSONResponse
from fastapi import Query
router = APIRouter()

@router.get("/pitch")
async def analyze_audio_pitch(filename: str, start: float = Query(0.0), end: float = Query(1.0)):
    try:
        base_dir = os.path.join(os.path.dirname(__file__), "../../audio_files")
        file_path = os.path.join(base_dir, filename)

        print(f"请求分析文件: {file_path}, start={start}, end={end}")

        if not os.path.exists(file_path):
            print(f"文件不存在: {file_path}")
            raise HTTPException(status_code=404, detail="文件不存在")

        result = analyze_pitch(file_path, start, end)

        print(
            f"分析结果：pitches长度={len(result['pitches'])}, "
            f"magnitudes长度={len(result['magnitudes'])}, "
            f"frame_count={result['frame_count']}, "
            f"main_pitches长度={len(result['main_pitches'])}"
        )

        return JSONResponse(content=result)

    except Exception as e:
        print("分析音频时发生异常：")
        traceback.print_exc()
        raise HTTPException(status_code=500, detail=str(e))

