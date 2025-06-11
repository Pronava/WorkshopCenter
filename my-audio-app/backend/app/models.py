from pydantic import BaseModel

class PitchAnalysis(BaseModel):
    pitches: list
    magnitudes: list
