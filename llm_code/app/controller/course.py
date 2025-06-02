from flask import Blueprint, render_template, request, jsonify, redirect, url_for, session
from app.models.base import db
from app.models.course import Course
from app.models.question import Question

courseBP = Blueprint('course', __name__)  # 创建一个蓝图，将其绑定到app上


@courseBP.route('/courseList', methods=['GET'])
def CourseList():
    course = request.args.get('course')
    courseType = request.args.get('courseType')
    topic = request.args.get('topic')
    subtopic = request.args.get('subtopic')
    score = request.args.get('score')
    print(score)
    if score and (int(score) < 0 or int(score) > 5):
        return jsonify({"code": 400, 'error': "score must be between 0 and 5"})

    query = Course.query.filter(Course.status == 1)
    if course:
        query = query.filter(Course.course == course)
    if courseType:
        query = query.filter(Course.courseType == courseType)
    courseList = query.all()
    result = []
    for item in courseList:
        query2 = Question.query.filter(Question.status == 1)
        query2 = query2.filter(Question.courseId == item.id)
        if topic:
            query2 = query2.filter(Question.topic == topic)
        if subtopic:
            query2 = query2.filter(Question.subtopic == subtopic)
        if score:
            query2 = query2.filter(Question.score <= score)
        questionList = query2.all()
        question_dicts = []
        for q in questionList:
            question_dicts.append(q.to_dict())
        result.append({
            'id': item.id,
            'course': item.course,
            'courseNumber': item.courseNumber,
            'courseType': item.courseType,
            'question': question_dicts
        })
    return jsonify({"code": 200, "data": result})


@courseBP.route('/add', methods=['POST'])
def add():
    data = request.get_json()  # 从请求中获取 JSON 数据

    # 检查请求数据是否包含所有必需的字段
    if not all(key in data for key in ['course', 'courseNumber', 'courseType']):
        return jsonify({'error': 'Missing required fields', 'code': 400}), 200
    if 'username' not in session:
        return jsonify({'error': 'Login expired', 'code': 400}), 200
    course = data['course']
    courseNumber = data['courseNumber']
    courseType = data['courseType']

    try:
        # 使用实验模型创建实例
        course = Course(0, course, courseNumber, courseType)
        # 添加实例到会话中
        db.session.add(course)
        # 提交事务
        db.session.commit()
    except Exception as e:
        print(e)
        # 出错时回滚事务
        db.session.rollback()
        return jsonify({'error': str(e), 'code': 500}), 200

    return jsonify({'error': "Course successful", 'code': 200}), 200


@courseBP.route('/get', methods=['get'])
def get():
    data = Course.query.all()
    return render_template('course.html', data=data)


@courseBP.route('/update', methods=['POST'])
def update():
    data = request.get_json()  # 从请求中获取 JSON 数据
    # 检查请求数据是否包含所有必需的字段
    if not all(key in data for key in ['id', 'status']):
        return jsonify({'error': 'Missing required fields', 'code': 400}), 200
    if 'username' not in session:
        return jsonify({'error': 'Login expired', 'code': 400}), 200
    Course.query.filter(Course.id == data['id']).update({'status': data['status']})
    db.session.commit()
    return jsonify({'error': "Course update successful", 'code': 200}), 200


maps = {'0': 'off line', '1': 'online', '2': 'under review'}


@courseBP.route('/management', methods=['GET'])
def management():
    data = Course.query.all()
    res = []
    for item in data:
        item.statusText = maps[str(item.status)]
        res.append(item)
    return render_template('courseManagement.html', data=res)
