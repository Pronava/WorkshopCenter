from flask import Blueprint, request, render_template, jsonify, session, redirect, url_for
from app.models.question import Question
from app.models.base import db
from app.models.comment import Comment
from app.models.user import User

questionBP = Blueprint('question', __name__)  # 创建一个蓝图，将其绑定到app上


@questionBP.route('/upload', methods=['GET', 'POST'])
def upload_file():
    if request.method == 'POST':
        file = request.files['file']
        if file:
            file.save('app/static/image/' + file.filename)
            file_path = '/static/image/' + file.filename
            return jsonify({'file_path': file_path, 'code': 200}), 200

    return jsonify({'code': 400}), 200


@questionBP.route('/my/question', methods=['GET'])
def question():
    if 'username' not in session:
        return jsonify({'error': 'Login expired', 'code': 400}), 200
    list = Question.query.filter(Question.uid == session['username']).all()
    return render_template('question.html', list=list)


@questionBP.route('/detail/<int:question_id>', methods=['GET'])
def detail(question_id):
    question = Question.query.filter(Question.id == question_id).first()
    list = Comment.query.join(User).filter(Comment.question_id == question_id).all()
    data = {
        'question': question,
        'listComment': list
    }
    return render_template('comment.html', data=data)


# id, text, LLMused, answer, answerType, score, topic, subtopic
@questionBP.route('/add', methods=['POST'])
def save_experiment():
    if request.method == 'GET':
        return render_template('.html')
    elif request.method == 'POST':
        data = request.get_json()  # 从请求中获取 JSON 数据

        # 检查请求数据是否包含所有必需的字段
        if not all(key in data for key in
                   ['courseId', 'text', 'LLMused', 'answer', 'answerType', 'score', 'topic', 'subtopic']):
            return jsonify({'error': 'Missing required fields', 'code': 400}), 200
        if 'username' not in session:
            return jsonify({'error': 'Login expired', 'code': 400}), 200
        # 从数据中提取字段
        oid = data.get('oid', None)
        text = data['text']
        LLMused = data['LLMused']
        answer = data['answer']
        answerType = data['answerType']
        score = data['score']
        topic = data['topic']
        subtopic = data['subtopic']
        courseId = data['courseId']
        uid = session['username']
        if score and (int(score) < 0 or int(score) > 5):
            return jsonify({"code": 400, 'error': "score must be between 0 and 5"}), 200
        # 尝试创建新的实验记录并保存到数据库
        try:
            # 使用实验模型创建实例
            question = Question(oid, courseId, uid, text, LLMused, answer, answerType, score, topic, subtopic, 0)
            # 添加实例到会话中
            db.session.add(question)
            # 提交事务
            db.session.commit()
        except Exception as e:
            print(e)
            # 出错时回滚事务
            db.session.rollback()
            return jsonify({'error': str(e)}), 500

        # 返回成功响应
        response = {'error': 'question added successfully', 'code': 200}
        return jsonify(response), 201


@questionBP.route('/update', methods=['POST'])
def update():
    data = request.get_json()  # 从请求中获取 JSON 数据
    # 检查请求数据是否包含所有必需的字段
    if not all(key in data for key in ['id', 'status']):
        return jsonify({'error': 'Missing required fields', 'code': 400}), 200
    if 'username' not in session:
        return jsonify({'error': 'Login expired', 'code': 400}), 200
    obj = Question.query.filter(Question.id == data['id']).first()
    Question.query.filter(Question.id == obj.oid).update({'status': 0})
    Question.query.filter(Question.id == data['id']).update({'status': data['status']})

    db.session.commit()
    return jsonify({'error': "Question update successful", 'code': 200}), 200


maps = {'0': 'off line', '1': 'online', '2': 'under review'}


@questionBP.route('/management', methods=['GET'])
def management():
    data = Question.query.all()
    res = []
    for item in data:
        item.statusText = maps[str(item.status)]
        res.append(item)
    return render_template('questionManagement.html', list=res)
