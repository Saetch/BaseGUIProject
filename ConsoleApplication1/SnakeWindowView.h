#pragma once
class SnakeWindowView
{
public:
	SnakeWindowView(int w, int h);
	~SnakeWindowView();
	int refreshIndex(int index);
private:


	int WIDTH;
	int HEIGHT;
};

