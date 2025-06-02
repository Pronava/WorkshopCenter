from sqlalchemy import Column, String, Integer,orm,ForeignKey
from app.models.base import Base
from app.models.base import db

class Course(Base):
    __tablename__ = 'course'
    id = Column("id",Integer,ForeignKey('question.course_id'), primary_key=True, autoincrement=True)
    course = Column('course',String(50))
    courseNumber = Column( 'course_number',String(50))
    courseType = Column('course_type',String(50))
    question = db.relationship('Question', backref='course',uselist=True)
    status = Column('status',Integer)

    def __init__(self,status, course, courseNumber, courseType):
        super(Course, self).__init__()
        self.course = course
        self.status = status
        self.courseNumber = courseNumber
        self.courseType = courseType

