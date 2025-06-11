import os
import numpy as np
import librosa

def save_audio_file(upload_file, save_path: str) -> str:
    # 获取文件的保存路径
    save_directory = os.path.dirname(save_path)
    
    # 确保目录存在
    os.makedirs(save_directory, exist_ok=True)
    
    # 保存文件
    with open(save_path, "wb") as buffer:
        buffer.write(upload_file.file.read())
    
    # 返回保存的文件路径
    return save_path

def extract_pitch(y, sr):
    f0, _, _ = librosa.pyin(y, fmin=librosa.note_to_hz('C2'), fmax=librosa.note_to_hz('C7'))
    return np.nan_to_num(f0)
