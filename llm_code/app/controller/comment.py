from flask import Blueprint, render_template, request, jsonify, redirect, url_for,session
from app.models.comment import Comment
from app.models.question import Question
from app.models.user import User
from app.models.base import db

commentBP = Blueprint('comment', __name__)  # 创建一个蓝图，将其绑定到app上

@commentBP.route('/commentList/<int:question_id>', methods=['GET'])
def commentList(question_id):
    question = Question.query.filter(Question.id == question_id).first()
    list = Comment.query.join(User).filter(Comment.question_id == question_id).all()
    data = {
        'question': question,
        'listComment': list
    }
    return render_template('comment.html', data=data)

@commentBP.route('/save', methods=['POST'])
def save():
    data = request.get_json()  # 从请求中获取 JSON 数据

    # 检查请求数据是否包含所有必需的字段
    if not all(key in data for key in ['question_id', 'text']):
        return jsonify({'error': 'Missing required fields', 'code': 400}), 200
    if 'username' not in session:
        return jsonify({'error': 'Login expired', 'code': 400}), 200
    question_id = data['question_id']
    text = data['text']
    uid = session['username']

    try:
        # 使用实验模型创建实例
        comment = Comment(uid, question_id, text)
        # 添加实例到会话中
        db.session.add(comment)
        # 提交事务
        db.session.commit()
    except Exception as e:
        print(e)
        # 出错时回滚事务
        db.session.rollback()
        return jsonify({'error': str(e),'code':200}), 500

    return jsonify({'error': "Comment successful",'code': 200}), 200
