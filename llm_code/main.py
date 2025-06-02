from app import create_app
from flask import render_template
# 调用 create_app() 方法返回flask的实例：app
app = create_app()

@app.route('/')
def index():
    return render_template('login.html')

if __name__ == '__main__':
    # 启动应用服务器, 我们使用本地
    app.run(debug=True, host='127.0.0.1', port=5000)
    #app.run(host='0.0.0.0', port=5001)