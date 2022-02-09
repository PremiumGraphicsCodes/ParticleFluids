import threading
import time

class Test1():
  def __init__(self):
    self.started = threading.Event()
    self.alive = True

  def __del__(self):
    self.kill()

  def begin(self):
    print("begin")
    self.thread = threading.Thread(target=self.func)
    self.thread.start()
    self.started.set()
    self.alive = True

  def end(self):
    self.started.clear()
    print("\nend")

  def kill(self):
    self.started.set()
    self.alive = False
    self.thread.join()

  def func(self):
    i = 0
    self.started.wait()
    while self.alive:
      i += 1
      print("{}\r".format(i), end="")
      self.started.wait()

test1 = Test1()
