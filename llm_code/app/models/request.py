from sqlalchemy import Column, String, Integer, orm, Enum, ForeignKey, Float
from app.models.base import Base


class Request(Base):
    _requestID = Column('rid', Integer, primary_key=True, autoincrement=True)
    _requestType = Column('requestType', Enum('ADD_COURSE', 'UPDATE_SCORE', 'EXPERIMENT'), nullable=False)
    qid = Column(Integer, ForeignKey('question.id'))  # 外键约束，处理”增加问题变体“逻辑
    _newScore = Column('newScore', Float)
    _newCourseCode = Column('newCourseCode', String(20))  # ”增加课程“逻辑
    _newCourseName = Column('newCourseName', String(50))
    _newCourseCategory = Column('newCourseCategory', String(20))
    _explanation = Column('Explanation', String(300))  # 改分数、增加课程
    status = Column(Enum('agreed', 'rejected', 'pending'), nullable=False)  # 受理状态

    def __init__(self, rtype, **kwargs):
        super(Request, self).__init__()
        self._requestType = rtype
        self.status = 'pending'

        # 情况一：增加问题变体（eid）
        # 情况二：增加课程（_newCourseCode,_newCourseName,_newCourseCategory,_explanation）
        # 情况三：更改分数（qid,_explanation）
        for key, value in kwargs.items():
            setattr(self, key, value)
