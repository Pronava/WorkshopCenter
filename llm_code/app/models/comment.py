from sqlalchemy import Column, String, Integer,orm, Enum, Float
from app.models.base import Base
from app.models.base import db


class Comment(Base):
    __tablename__ = 'comment'
    id = Column(Integer, primary_key=True, autoincrement=True)
    question_id = Column('question_id', Integer)
    uid = Column('uid', Integer)
    text = Column('text', String(50))
    user = db.relationship('User', backref='comment')

    def __init__(self,uid, question_id, text):
        super(Comment, self).__init__()
        self.uid = uid
        self.question_id = question_id
        self.text = text
