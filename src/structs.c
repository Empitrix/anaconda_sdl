enum BLOCK_ACT{A_HEAD, A_BODY, A_POINT};

struct BLOCK {
	int x;
	int y;
	enum BLOCK_ACT act;
};


enum DIRECTION {D_LEFT, D_RIGHT, D_UP, D_DOWN};
