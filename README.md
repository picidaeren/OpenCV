# OpenCV
OpenCV&amp;&amp;C++进行模板匹配


matchTemplate实现了模版匹配算法，其中可用的方法有六个：

1.平方差匹配： method = CV_TM_SQDIFF
特点：这类方法利用平方差来进行匹配最好匹配为0.匹配差越大，匹配值越大。

![](https://github.com/picidaeren/OpenCV/blob/master/1.png)



2.标准平方差匹配：method = CV_TM_SQDIFF_NORMED
特点：这类方法利用平方差来进行匹配最好匹配为0.匹配差越大，匹配值越大。

![](https://github.com/picidaeren/OpenCV/blob/master/2.png)



3.相关匹配method=CV_TM_CCORR
特点：这类方法采用模板和图像间的乘法操作,所以较大的数表示匹配程度较高,0标识最坏的匹配效果.

![](https://github.com/picidaeren/OpenCV/blob/master/3.png)



4.标准相关匹配 method=CV_TM_CCORR_NORMED
特点：同标准平方差和平方差，以下不再赘述。

![](https://github.com/picidaeren/OpenCV/blob/master/4.png)



5.相关匹配 method=CV_TM_CCOEFF
特点：这类方法将模版对其均值的相对值与图像对其均值的相关值进行匹配,1表示完美匹配,-1表示糟糕的匹配,0表示没有任何相关性(随机序列).

![](https://github.com/picidaeren/OpenCV/blob/master/5.png)



6.标准相关匹配 method=CV_TM_CCOEFF_NORMED
特点：通常,随着从简单的测量(平方差)到更复杂的测量(相关系数),我们可获得越来越准确的匹配(同时也意味着越来越大的计算代价). 最好的办法是对所有这些设置多做一些测试实验,以便为自己的应用选择同时兼顾速度和精度的最佳方案.


![](https://github.com/picidaeren/OpenCV/blob/master/6.png)


