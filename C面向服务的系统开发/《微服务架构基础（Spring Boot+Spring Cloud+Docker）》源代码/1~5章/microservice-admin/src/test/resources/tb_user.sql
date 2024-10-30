# 创建一个名称为tb_user的表
CREATE TABLE tb_user (
  id int(32) PRIMARY KEY AUTO_INCREMENT,
  username varchar(32),
  address varchar(256)
 );
# 插入3条数据
INSERT INTO tb_user VALUES ('1', '小韩', '北京市海淀区');
INSERT INTO tb_user VALUES ('2', '小石', '北京市昌平区');
INSERT INTO tb_user VALUES ('3', '小陈', '北京市顺义区');