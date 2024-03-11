#pragma once

class Bitmap;

class DetailsPanel
{
public:
	DetailsPanel();
	~DetailsPanel();
	
	void Update();
	void ChangeObj(Bitmap* objChangeto);

private:
	Bitmap* selectedObjDeets;

};