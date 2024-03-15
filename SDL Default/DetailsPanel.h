#pragma once
#include <vector>

class Bitmap;

/// @brief main details panel setup 
class DetailsPanel
{
public:
	DetailsPanel(std::vector<Bitmap*>* hier);
	~DetailsPanel();
	
	void Update();
	void ChangeObj(Bitmap* objChangeto);

private:
	Bitmap* selectedObjDeets;
	std::vector<Bitmap*>* hier;
};