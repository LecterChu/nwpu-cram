# 使用Docker官方的Python作为一个基础镜像
FROM python:2.7-slim
# 设置工作目录/app
WORKDIR /app
# 复制当前目录下的所有内容到容器内的/app目录下
ADD . /app
# 安装在requirements.txt文件中声明的文件包
RUN pip install -r requirements.txt
# 设置容器暴露的端口为80
EXPOSE 80
# 定义环境变量
ENV NAME World
# 当容器启动后立即运行app.py
CMD ["python", "app.py"]
