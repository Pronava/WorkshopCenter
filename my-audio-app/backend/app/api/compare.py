from fastapi import APIRouter, UploadFile, File
import librosa
import numpy as np
import os
import tempfile

router = APIRouter()

@router.post("/compare")
async def compare_recorded(file: UploadFile = File(...)):
    with tempfile.NamedTemporaryFile(delete=False, suffix=".webm") as tmp:
        content = await file.read()
        tmp.write(content)
        tmp_path = tmp.name

    try:
        y, sr = librosa.load(tmp_path)
        hop_length = 256
        pitches, mags = librosa.piptrack(y=y, sr=sr, hop_length=hop_length)
        main_pitches = []

        for t in range(pitches.shape[1]):
            mag = mags[:, t]
            idx = np.argmax(mag)
            pitch = pitches[idx, t]
            main_pitches.append(float(pitch))

        return {
            "status": "success",
            "main_pitches": main_pitches[:100]  # 简化返回
        }
    except Exception as e:
        return {"status": "error", "detail": str(e)}
    finally:
        os.remove(tmp_path)
