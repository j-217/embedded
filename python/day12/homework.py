'''
@Author: ru_j
@Date: 2020-03-17 20:29:24
@LastEditTime: 2020-03-18 09:55:36
@Description:
'''
import tensorflow as tf
import os


def linear_gds():
    """
    y = 0.7x + 1.2
    """
    # 线性回归公式参数
    x = tf.random_normal([100, 1], mean=0.0, stddev=1.0)
    w = tf.Variable(initial_value=tf.random_normal(shape=[1, 1]))
    b = tf.Variable(initial_value=tf.random_normal(shape=[1, 1]))
    init = tf.global_variables_initializer()
    # 真实值
    true_y = tf.matmul(x, [[0.7]]) + 1.2
    # 预测值
    predict_y = tf.matmul(x, w) + b
    # 损失 平方差公式
    loss = tf.reduce_mean(tf.square(true_y - predict_y))
    # 使用梯度下降进行训练
    train_op = tf.train.GradientDescentOptimizer(0.01).minimize(loss)
    # 开启会话执行操作
    with tf.Session() as sess:
        sess.run(init)
        # 训练200次
        for i in range(200):
            sess.run(train_op)
            _loss = sess.run(loss)
            print('第{}次： loss={}'.format(i+1, _loss))


def read_file():
    # 读取文件夹内容
    dir_path = os.path.dirname(__file__) + '/dog/'
    files = os.listdir(dir_path)
    # 生成带文件路径的一阶向量
    files_list = [dir_path + _ for _ in files]
    # 生成批处理目标
    img_batch = batch_img(files_list)

    with tf.Session() as sess:
        # 实例化协调器
        coor = tf.train.Coordinator()
        # 多线程处理
        threads = tf.train.start_queue_runners(sess=sess, coord=coor)
        # 启动会话
        result = sess.run(img_batch)
        print(result)
        # 回收线程
        coor.request_stop()
        coor.join(threads=threads)


def batch_img(files_list):
    # 构造文件名队列
    files_queue = tf.train.string_input_producer(files_list)
    # 构造读取器
    reader = tf.WholeFileReader()
    # 读取文件
    key, value = reader.read(files_queue)
    # 图片解码
    img_dec = tf.image.decode_jpeg(value)
    # 调整图片大小
    img_res = tf.image.resize_images(img_dec, [200, 200])
    print(img_res)
    # 改变形状
    img_res.set_shape([200, 200, 3])
    # 生成批处理
    img_batch = tf.train.batch([img_res], batch_size=100, capacity=100,
                               num_threads=1)
    return img_batch


if __name__ == "__main__":
    # linear_gds()
    read_file()
