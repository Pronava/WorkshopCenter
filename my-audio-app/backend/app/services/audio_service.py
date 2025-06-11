import os  # 需要导入 os 模块
import librosa
import numpy as np

import librosa

import librosa
import numpy as np

def analyze_pitch(file_path: str, start: float = 0, end: float = 1):
    # 加载音频的指定片段
    duration = end - start
    y, sr = librosa.load(file_path, offset=start, duration=duration)

    # 设置更小的 hop_length 增加时间分辨率
    hop_length = 256
    n_fft = 1024

    pitches, magnitudes = librosa.piptrack(y=y, sr=sr, n_fft=n_fft, hop_length=hop_length)

    # 计算每帧主频
    main_pitches = []
    time_frames = pitches.shape[1]

    for t in range(time_frames):
        pitch_slice = pitches[:, t]
        mag_slice = magnitudes[:, t]
        if mag_slice.size == 0:
            main_pitches.append(0)
            continue
        max_idx = np.argmax(mag_slice)
        main_pitch = pitch_slice[max_idx]
        main_pitches.append(float(main_pitch))

    return {
        "pitches": pitches.tolist(),
        "magnitudes": magnitudes.tolist(),
        "main_pitches": main_pitches,
        "sr": sr,
        "hop_length": hop_length,
        "frame_count": time_frames
    }


def save_audio_file(upload_file, save_path: str) -> str:
    # 获取文件的保存路径
    save_directory = os.path.dirname(save_path)
    
    # 确保目录存在
    os.makedirs(save_directory, exist_ok=True)
    
    # 打印文件保存的路径
    print(f"Saving file to: {save_path}")
    
    # 保存文件
    with open(save_path, "wb") as buffer:
        buffer.write(upload_file.file.read())
    
    # 打印保存成功的消息
    print(f"File saved successfully: {save_path}")
    
    # 返回保存的文件路径
    return save_path
