import json
class Good:
    # 编号pid  品名：pname,价格：price,数量：num,小计:acount,出厂日期：pdate
    def __init__(self,pid,pname,price,num,pdate):
        self.pid = pid
        self.pname = pname
        self.price = price
        self.num = num
        self.pdate = pdate
        self.acount = price * num
    def __str__(self):
        return (
f"""编号: {self.pid}
品名: {self.pname}
价格: {self.price}
数量: {self.num}
小计: {self.acount}
出厂日期: {self.pdate}"""
        )
    def __repr__(self):
        return self.__str__()
    def __eq__(self,other):
        return self.pid == other.pid
    def __lt__(self,other):
        return self.price < other.price
    def __gt__(self,other):
        return self.price > other.price
    def __le__(self,other):
        return self.price <= other.price
    def __ge__(self,other):
        return self.price >= other.price
    def __ne__(self,other):
        return self.price != other.price

class GoodManager:
    def __init__(self,*args):
        # 商品列表(list)
        self.goods = []
        if args:
            for good in args:
                self.goods.append(good)
    def add(self,good):
        self.goods.append(good)
    def remove(self,good):
        self.goods.remove(good)
    def __str__(self):
        return "\n".join([str(good) for good in self.goods])
    def __repr__(self):
        return self.__str__()
    def sort(self):
        self.goods.sort(key=lambda good:good.pid)
    def sort_by_price(self):
        self.goods.sort(key=lambda good:good.price)
    def sort_by_num(self):
        self.goods.sort(key=lambda good:good.num)
    def sort_by_pname(self):
        self.goods.sort(key=lambda good:good.pname)
    def search(self,pid):
        for good in self.goods:
            if good.pid == pid:
                return good
        return None
    def update(self,good):
        for i in range(len(self.goods)):
            if self.goods[i] == good:
                self.goods[i] = good
                break
    def get(self):
        return self.goods
    def __iter__(self):
        return iter(self.goods)
    def __next__(self):
        return next(self.goods)
    def __getitem__(self,index):
        return self.goods[index]
    def __len__(self):
        return len(self.goods)
    def format_to_dict(self):
        return {good.pid:good.__dict__ for good in self.goods}
    def format_to_list(self):
        return [good.__dict__ for good in self.goods]
    def format_to_json(self):
        return json.dumps(self.format_to_list())
    def from_dict(self,dict):
        self.goods = [Good(**good) for good in dict.values()]
    def from_list(self,list):
        self.goods = [Good(**good) for good in list]
    def from_json(self,json_str):
        self.goods = [Good(**good) for good in json.loads(json_str)]
    def save(self,filename):
        with open(filename,"w") as f:
            f.write(self.format_to_json())
    def load(self,filename):
        with open(filename,"r") as f:
            self.from_json(f.read())
    def __add__(self,other):
        return GoodManager(*self.goods,*other.goods)
    def __sub__(self,other):
        return GoodManager(*[good for good in self.goods if good not in other.goods])
    def __and__(self,other):
        return GoodManager(*[good for good in self.goods if good in other.goods])
    def __or__(self,other):
        return GoodManager(*self.goods,*[good for good in other.goods if good not in self.goods])
    def __contains__(self,good):
        return good in self.goods
    def __next__(self):
        return next(self.goods)
    
if __name__ == "__main__":
    # 商品编号：1，品名：apple，价格：5，数量：100，出厂日期：2020-1-1
    g1 = Good(1,"apple",5,100,"2020-1-1")
    g2 = Good(2,"banana",3,200,"2020-1-2")
    g3 = Good(3,"orange",4,150,"2020-1-3")
    # 商品管理器(内部用列表存储商品对象)
    gm = GoodManager(g1,g2,g3)
    print("商品管理器：\n",gm)
    print("字典形式：",gm.format_to_dict())
    print("列表形式：",gm.format_to_list())
    print("Json：",gm.format_to_json())
    
    while True:
        print("add:添加商品")
        print("remove:删除商品")
        print("search:查找商品")
        print("update:修改商品")
        print("save:保存商品")
        print("load:加载商品")
        print("exit:退出")

        input_str = input("输入操作：")
        if input_str == "add":
            pid = input("输入商品编号：")
            pname = input("输入品名：")
            price = input("输入价格：")
            num = input("输入数量：")
            pdate = input("输入出厂日期：")
            gm.add(Good(pid,pname,price,num,pdate))
            print("添加成功")
        elif input_str == "remove":
            pid = input("输入商品编号：")
            good = gm.search(pid)
            if good:
                gm.remove(good)
                print("删除成功")
            else:
                print("商品不存在")
        elif input_str == "search":
            pid = input("输入商品编号：")
            good = gm.search(pid)
            if good:
                print(good)
            else:
                print("商品不存在")
        elif input_str == "update":
            pid = input("输入商品编号：")
            good = gm.search(pid)
            if good:
                pname = input("输入品名：")
                price = input("输入价格：")
                num = input("输入数量：")
                pdate = input("输入出厂日期：")
                good.pname = pname
                good.price = price
                good.num = num
                good.pdate = pdate
                gm.update(good)
                print("修改成功")
            else:
                print("商品不存在")
        elif input_str == "save":
            filename = input("输入文件名：")
            gm.save(filename)
            print("保存成功")
        elif input_str == "load":
            filename = input("输入文件名：")
            gm.load(filename)
            print("加载成功")
        elif input_str == "exit":
            break
        else:
            print("无效操作")