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
    def __init__(self, *args):
        # 商品字典(dict)
        self.goods = {}
        if args:
            for good in args:
                self.goods[good.pid] = good

    def add(self, good):
        self.goods[good.pid] = good

    def remove(self, good):
        if good.pid in self.goods:
            del self.goods[good.pid]

    def __str__(self):
        return "\n".join([str(good) for good in self.goods.values()])

    def __repr__(self):
        return self.__str__()

    def sort(self):
        # 返回排序后的商品列表
        return sorted(self.goods.values(), key=lambda good: good.pid)

    def sort_by_price(self):
        return sorted(self.goods.values(), key=lambda good: good.price)

    def sort_by_num(self):
        return sorted(self.goods.values(), key=lambda good: good.num)

    def sort_by_pname(self):
        return sorted(self.goods.values(), key=lambda good: good.pname)

    def search(self, pid):
        return self.goods.get(pid, None)

    def update(self, good):
        if good.pid in self.goods:
            self.goods[good.pid] = good

    def get(self):
        return list(self.goods.values())

    def __iter__(self):
        self._iter_index = iter(self.goods.values())
        return self

    def __next__(self):
        return next(self._iter_index)

# 示例使用
if __name__ == "__main__":
    gm = GoodManager()
    gm.add(Good(1, "Apple", 10, 100, "2021-01-01"))
    gm.add(Good(2, "Banana", 20, 150, "2021-01-02"))
    print(gm)
    for good in gm:
        print(good)