from flask import Flask
from app.controller import user, course,question,comment,request


# 定义注册蓝图方法, 将所有的蓝图注册到app上
def register_blueprints(app):

    app.register_blueprint(user.userBP, url_prefix='/user')
    app.register_blueprint(course.courseBP, url_prefix='/course')
    app.register_blueprint(question.questionBP, url_prefix='/question')
    app.register_blueprint(comment.commentBP, url_prefix='/comment')

    app.register_blueprint(request.requestBP, url_prefix='/request')



# 注册插件(关联数据库)
def register_plugin(app):
    from app.models.base import db
    db.init_app(app)
    # create_all要放到app上下文环境中使用
    with app.app_context():
        db.create_all()


def create_app():
    app = Flask(__name__)
    app.secret_key = '123456789++'
    app.config["SQLALCHEMY_ECHO"] = True
    app.config.from_object('app.config.secure')  # 重要参数配置(secure.py)
    # 注册蓝图与app对象相关联
    register_blueprints(app)
    # 注册插件(数据库)与app对象相关联
    register_plugin(app)
    return app
