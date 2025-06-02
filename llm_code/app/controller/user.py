from flask import Blueprint, render_template, request, jsonify, redirect, url_for, session
from app.models.base import db
from app.models.student import Student
from app.models.teacher import Teacher
from app.models.admin import Admin
from app.models.user import User
from sqlalchemy import or_, and_, all_, any_, text
import re
import uuid
from app.config.email import send_email2

userBP = Blueprint('user', __name__)  # 创建一个蓝图，将其绑定到app上

# 第三方 SMTP 服务
mail_host = "smtp.qq.com"  # SMTP服务器
mail_user = "1553672602@qq.com"  # 用户名
mail_pass = "xjmacxqwdcspjija"  # 授权密码，非登录密码

sender = '1553672602@qq.com' # 发件人邮箱(最好写全, 不然会失败) # 接收邮件，可设置为你的QQ邮箱或者其他邮箱
title = 'Register activation email'  # 邮件主题


@userBP.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'GET':
        return render_template('register.html')
    elif request.method == 'POST':
        email = request.form.get('email')
        _password = request.form.get('password1')
        __password = request.form.get('password2')
        pattern1 = r'@mail\.uic\.edu\.cn$'  # 正则检查，表示用户注册的账号是学生账号
        pattern2 = r'@uic\.edu\.cn$'  # 正则检查，表示用户注册的账号是教师账号
        uuids = str(uuid.uuid1())
        receivers = email
        if _password == __password:
            if re.search(pattern1, email):
                with db.auto_commit():
                    student = Student(email, _password, uuids, 0)
                    db.session.add(student)
                    content = "Click this link to activate your account: <a href=" + "http://127.0.0.1:5000/user/activate?id=" + email + "&uuids=" + uuids + ">http://127.0.0.1:5000/user/activate?id=" + email + "&uuids=" + uuids + "</a>"
                    send_email2(mail_host, mail_user, mail_pass, receivers, title, content)
                # return 'Register success'
                # return 'Please open your email to activate!'
                return render_template('success.html',
                                       message='Please open your email to activate!')  # 注册成功返回到哪个页面呢，需要改进

            elif re.search(pattern2, email):
                with db.auto_commit():
                    teacher = Teacher(email, _password, uuids, 0)
                    db.session.add(teacher)
                    content = "Click this link to activate your account: <a href=" + "http://127.0.0.1:5000/user/activate?id=" + email + "&uuids=" + uuids + ">http://127.0.0.1:5000/user/activate?id=" + email + "&uuids=" + uuids + "</a>"
                    send_email2(mail_host, mail_user, mail_pass, receivers, title, content)
                # return 'Register success'
                # return 'Please open your email to activate!'
                return render_template('success.html', message='Please open your email to activate!')
                # return render_template('**.html',title='Success Register')  # 注册成功返回到哪个页面呢，需要改进

            else:  # 输入的不是UIC邮箱，不能注册
                return render_template('error.html', message='Your email address has no registration rights')
                # return 'Your email address has no registration rights'
                # return render_template('**.html',title='Fail Register')  # 注册失败返回到哪个页面呢，需要改进
        else:
            return render_template('error.html', message='Ensure that the two passwords are the same!')
            # return 'Ensure that the two passwords are the same!'
            # return render_template('**.html',title='Fail Register')
    else:
        return render_template('error.html', message='Fail to register')
        # return 'Fail to register'


@userBP.route('/activate', methods=['GET'])
def activate():
    email = request.args.get('id', '')
    uuids = request.args.get('uuids', '')
    sql = text("UPDATE user SET status = :status WHERE code = :code And email = :email ")
    try:
        db.session.execute(sql, {'status': 1, 'code': uuids, 'email': email})
        db.session.commit()
        return redirect(url_for('user.login'))
    except:
        db.rollback()
        return render_template('error.html', message='Activation fails')


@userBP.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'GET':
        return render_template('login.html')
    elif request.method == 'POST':
        email = request.form.get('email')
        _password = request.form.get('password')
        identify = request.form.get('usertype')  # 表单中，usertype是name属性， identify是value属性

        if identify == 'teacher':
            result = Teacher.query.filter(
                and_(Teacher.status == 1, Teacher.email == email, Teacher._password == _password,
                     Teacher.userType == identify)).first()
            if result:
                session['username'] = result['id']
                # return 'Teacher Login Success'
                return redirect(url_for('user.teacher'))  # 去教师的主页
            else:
                return 'User not exists!'
                # return render_template('login.html')
        elif identify == 'student':
            result = Student.query.filter(
                and_(Student.status == 1, Student.email == email, Student._password == _password,
                     Student.userType == identify)).first()
            if result:
                session['username'] = result['id']
                # return 'Student Login Success'
                return redirect(url_for('user.student'))  # 去学生的主页
            else:
                return 'User not exists!'
                # return render_template('login.html')
        elif identify == 'admin':
            result = Admin.query.filter(
                and_(Admin.status == 1, Admin.email == email, Admin._password == _password,
                     Admin.userType == identify)).first()
            if result:
                session['username'] = result['id']
                # return 'Administrator Login Success'
                return redirect(url_for('user.admin'))  # 去管理员的主页
            else:
                return 'User not exists!'
                # return render_template('login.html')
        else:
            return 'Please choose your identity!'

    else:
        return "Error to submit form"


@userBP.route('/admin', methods=['GET', 'POST'])
def admin():
    return render_template('admin.html')


@userBP.route('/student', methods=['GET', 'POST'])
def student():
    return render_template('student.html')


@userBP.route('/teacher', methods=['GET', 'POST'])
def teacher():
    return render_template('teacher.html')


@userBP.route('/management', methods=['GET'])
def management():
    return render_template('userManagement.html')
