from fastapi import APIRouter, WebSocket, WebSocketDisconnect
import numpy as np

router = APIRouter()

@router.websocket("/ws/audio-stream")
async def audio_stream(websocket: WebSocket):
    await websocket.accept()
    print("WebSocket 已接受连接")
    try:
        while True:
            data = await websocket.receive_bytes()
            print(f"接收到音频数据，长度：{len(data)} bytes")
            pcm = np.frombuffer(data, dtype=np.int16).astype(np.float32) / 32768.0

            fft = np.fft.fft(pcm)
            freq = np.fft.fftfreq(len(pcm), 1 / 44100)
            magnitude = np.abs(fft)
            peak_idx = np.argmax(magnitude[:len(magnitude)//2])
            pitch = float(freq[peak_idx])

            print(f"计算出的音高：{pitch:.2f} Hz")
            await websocket.send_json({"pitches": [round(pitch, 2)]})
    except WebSocketDisconnect:
        print("客户端断开 WebSocket 连接")
    except Exception as e:
        print("WebSocket 错误或关闭:", e)
