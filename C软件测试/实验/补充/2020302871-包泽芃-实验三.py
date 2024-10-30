# -*- coding = utf-8 -*-
# @Time : 2022/10/21 15:32
# @Author : BaoZepeng

import time
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.common.action_chains import ActionChains
from selenium.webdriver.chrome.service import Service

# 版本更新后，executable_path被重构到了 Service 函数里
s = Service("C:/Users/64380/AppData/Local/Google/Chrome/Application/chromedriver")
driver = webdriver.Chrome(service=s)
# 测试网址：https://nj.zu.anjuke.com/
driver.get("https://nj.zu.anjuke.com/")
# 最大化浏览器
driver.maximize_window()
# driver.implicitly_wait(30)
time.sleep(3)
# 1. 打开安居客网页版，点击租房
driver.find_element(by=By.XPATH,value='/html/body/div[2]/div/ul/li[4]/a').click()
time.sleep(3)
# 2. 地址选择“南京”
# 定位到要悬停的元素
above = driver.find_element(by=By.ID,value='switch_apf_id_5')
time.sleep(3)
# 对定位到的元素执行鼠标悬停操作
ActionChains(driver).move_to_element(above).perform()
time.sleep(3)
# 点击南京
driver.find_element(by=By.XPATH,value='//*[@id="city_list"]/dl[2]/dd/a[4]').click()
time.sleep(3)
# 3. 点击“地铁找房”
driver.find_element(by=By.XPATH,value='/html/body/div[4]/ul/li[2]/a').click()
time.sleep(3)
# 4. 选择“2 号线”
driver.find_element(by=By.XPATH,value='/html/body/div[5]/div[2]/div[1]/span[2]/div/a[3]').click()
time.sleep(3)
# 5. 选择“马群”
driver.find_element(by=By.XPATH,value='/html/body/div[5]/div[2]/div[1]/span[2]/div/div/a[24]').click()
time.sleep(3)
# 6. 设置租金为 5000-8000 元，并点击确定
# 对id为from-price的输入框输入5000
driver.find_element(by=By.ID,value='from-price').send_keys(5000)
time.sleep(3)
# 对id为to-price的输入框输入8000
driver.find_element(by=By.ID,value='to-price').send_keys(8000)
time.sleep(3)
# 点击确定
driver.find_element(by=By.ID,value='pricerange_search').click()
time.sleep(3)
# 7. 选择“整租”
driver.find_element(by=By.XPATH,value='/html/body/div[5]/div[2]/div[4]/span[2]/a[2]').click()
time.sleep(3)
# 8. 房屋类型选择“普通住宅”
# 点击房屋类型下拉列表
driver.find_element(by=By.ID,value='condhouseage_txt_id').click()
time.sleep(3)
# 选择“普通住宅”
driver.find_element(by=By.XPATH,value='//*[@id="condmenu"]/ul/li[2]/ul/li[2]/a').click()
time.sleep(3)
# 9. 在搜索框中搜索“经天路”，并点击“搜索”
# 点击输入框
driver.find_element(by=By.ID,value='search-rent').click()
time.sleep(3)
# 输入'经天路'
driver.find_element(by=By.ID,value='search-rent').send_keys('经天路')
time.sleep(3)
# 点击“搜索”
driver.find_element(by=By.ID,value='search-button').click()
time.sleep(3)
# 10. 选择“视频看房”
driver.find_element(by=By.XPATH,value='//*[@id="list-content"]/div[1]/a[2]').click()
time.sleep(3)
# 11. 依次点击“租金”、“最新”排序进行查看
# 点击租金
driver.find_element(by=By.XPATH,value='//*[@id="list-content"]/div[2]/div/a[2]').click()
time.sleep(3)
# 点击最新
driver.find_element(by=By.XPATH,value='//*[@id="list-content"]/div[2]/div/a[3]').click()
time.sleep(3)
# 12. 点击第一个搜索出来的房源进行查看
driver.find_element(by=By.XPATH,value='//*[@id="list-content"]/div[3]').click()
time.sleep(3)
# 关闭
driver.close()