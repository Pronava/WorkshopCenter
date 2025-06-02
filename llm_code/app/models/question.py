from sqlalchemy import Column, String, Integer, ForeignKey, Enum, Float
from app.models.base import Base


class Question(Base):
    __tablename__ = 'question'
    id = Column('id',Integer, primary_key=True, autoincrement=True)
    oid = Column('oid', Integer)
    uid = Column('uid', Integer)
    courseId = Column('course_id', Integer)
    text = Column('text', String(6400))
    LLMused = Column('used', String(50))
    answer = Column('answer', String(500))
    answerType = Column('answer_type', Enum('text', 'img'), nullable=False)
    score = Column('score', Float)
    topic = Column('topic', String(50))
    subtopic = Column('subtopic', String(50))
    def __init__(self,oid, courseId, uid, text, LLMused, answer, answerType, score, topic, subtopic, status):
        super(Question, self).__init__()
        self.oid = oid
        self.courseId = courseId
        self.uid = uid
        self.text = text
        self.LLMused = LLMused
        self.answer = answer
        self.answerType = answerType
        self.score = score
        self.topic = topic
        self.subtopic = subtopic
        self.status =status

    def to_dict(self):
        return {
            'uid': self.uid,
            'id': self.id,
            'text': self.text,
            'LLMused': self.LLMused,
            'answer': self.answer,
            'answerType': self.answerType,
            'score': self.score,
            'topic': self.topic,
            'subtopic': self.subtopic,
            'status': self.status
        }
