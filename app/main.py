from kivy.app import App
from kivy.uix.button import Button
from kivy.uix.boxlayout import BoxLayout

class Container(BoxLayout):
	pass

class TestApp(App):
	def build(self):
		self.load_kv('my.kv')
		return Container()

if __name__ == '__main__':
    TestApp().run()
