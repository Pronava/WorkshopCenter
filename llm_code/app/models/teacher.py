from app.models.user import User


class Teacher(User):
    __tablename__ = None  # 不要单独创建表,合并到父类
    def __init__(self, email, pwd,code, status,):
        super().__init__(email, pwd, code, status,userType='Teacher')
