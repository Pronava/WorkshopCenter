from sqlalchemy import Column, String, ForeignKey,Integer, Enum
from app.models.base import Base

class User(Base):
    __tablename__ = 'user'
    id = Column("id",Integer, ForeignKey('comment.uid'),primary_key=True, autoincrement=True,)
    email = Column('email',String(50))
    _password = Column('password', String(100))
    userType = Column('user_type',Enum('Teacher', 'Student', 'Admin'), nullable=False)
    code = Column('code', String(100))
    def __init__(self, email, password,code,status,userType):
        super(User, self).__init__()
        self.email = email
        self._password = password
        self.code = code
        self.status = status
        self.userType = userType

    @property
    def password(self):
        return self._password
