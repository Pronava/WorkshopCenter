from app.models.user import User


class Student(User):
    __tablename__ = None  # 不要单独创建表,合并到父类

    def __init__(self, email, password, code, status):
        super().__init__(email, password, code, status, userType='Student')
