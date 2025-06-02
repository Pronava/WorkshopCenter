from flask import Blueprint, render_template, request, jsonify, redirect, url_for
from app.models.base import db
from app.models.request import Request

requestBP = Blueprint('request', __name__)  # 创建一个蓝图，将其绑定到app上

@requestBP.route('/register', methods=['GET', 'POST'])
def register():
    Request
    return render_template('register.html')