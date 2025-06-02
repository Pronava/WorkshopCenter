from app.models.user import User


class Admin(User):
    __tablename__ = None  # 不要单独创建表,合并到父类

    def __init__(self, email, pwd):
        super().__init__(email, pwd, userType='Admin')
