import pymysql as sql

class SQLManager:
    def __init__(self,host='localhost',port=3306,user='root',password='',database='',charset='utf8'):
        self.host = host
        self.port = port
        self.database = database
        self.user = user
        self.database = database
        self.charset = charset
        if database == '':
            raise ValueError('database must be not empty')
        try:
            self.conn = sql.connect(
                host=host,
                port=port,
                user=user,
                password=password,
                database=database,
                charset=charset
            )
        except Exception as e:
            print('Connect failed:',e)
            raise e
        self.cursor = self.conn.cursor()
    def __del__(self):
        if not hasattr(self,'cursor'):
            return
        self.cursor.close()
    def query(self,sql):
        self.cursor.execute(sql)
        return self.cursor.fetchall()
    def update(self,sql):
        self.cursor.execute(sql)
        self.conn.commit()
    def insert(self,sql):
        self.cursor.execute(sql)
        self.conn.commit()
    def delete(self,sql):
        self.cursor.execute(sql)
        self.conn.commit()
    def close(self):
        self.cursor.close()
        self.conn.close()
    def __str__(self):
        # 返回当前数据库的连接信息
        return f"{self.user}@{self.host}:{self.port}/{self.database}?charset={self.charset}"
