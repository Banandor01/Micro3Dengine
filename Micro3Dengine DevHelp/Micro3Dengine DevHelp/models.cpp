#include "models.h"

const Vector3D<float> Cubevectors[8] = PROGMEM {
	{ -3.0f, 3.0f, -3.0f },
	{ 3.0f, 3.0f, -3.0f },
	{ -3.0f, -3.0f, -3.0f },
	{ 3.0f, -3.0f, -3.0f },
	{ -3.0f, 3.0f, 3.0f },
	{ 3.0f, 3.0f, 3.0f, },
	{ -3.0f, -3.0f, 3.0f },
	{ 3.0f, -3.0f, 3.0f },
};

extern const Face cubeFaces[12] = PROGMEM {
	{0, 1, 2},    // side 1
	{2, 1, 3},
	{4, 0, 6},    // side 2
	{6, 0, 2},
	{7, 5, 6},    // side 3
	{6, 5, 4},
	{3, 1, 7},    // side 4
	{7, 1, 5},
	{4, 5, 0},    // side 5
	{0, 5, 1},
	{3, 7, 2},    // side 6
	{2, 7, 6},
};

extern const Vector3D<float> bridgeVectors[119] = PROGMEM{
	{-6.74957 , 1.58425f , 1.86094f }  ,
	{-5.54318 , -0.095537 , 1.91708f }  ,
	{-6.7891 , -0.108046 , 1.82758 }  ,
	{-5.59739 , 1.33605 , 1.93901 }  ,
	{-5.24034 , 2.72271 , 1.9896 }  ,
	{-6.24615 , 3.19945 , 1.92614 }  ,
	{-6.65417 , 1.60826 , 0.529569 }  ,
	{-6.15076 , 3.22346 , 0.594769 }  ,
	{-5.14495 , 2.74672 , 0.658236 }  ,
	{-5.502 , 1.36006 , 0.607645 }  ,
	{-6.69371 , -0.084034 , 0.496215 }  ,
	{-5.44779 , -0.071525 , 0.585709 }  ,
	{-4.40658 , 3.97231 , 0.733243 }  ,
	{-4.50197 , 3.94829 , 2.06461 }  ,
	{-5.31786 , 4.61239 , 2.01813 }  ,
	{-5.22247 , 4.6364 , 0.686763 }  ,
	{-3.34873 , 4.93414 , 0.826384 }  ,
	{-3.44412 , 4.91013 , 2.15775 }  ,
	{-4.03666 , 5.71355 , 2.12979 }  ,
	{-3.94127 , 5.73757 , 0.79842 }  ,
	{-2.05999 , 5.55166 , 0.929858 }  ,
	 {-2.15538 , 5.52765 , 2.26123 }  ,
	 {-0.74374 , 5.74914 , 2.36636 }  ,
	 {-2.50179 , 6.41762 , 2.25246 }  ,
	 {-2.4064 , 6.44163 , 0.921089 }  ,
	 {-0.648349 , 5.77315 , 1.03499 }  ,
	 {0.672582 , 5.55604 , 2.46436 }  ,
	 {0.767972 , 5.58005 , 1.13299 }  ,
	 {1.97495 , 4.96453 , 2.547 }  ,
	 {2.07034 , 4.98854 , 1.21563 }  ,
	 {3.05425 , 4.02416 , 2.60737 }  ,
	 {3.14964 , 4.04817 , 1.276 }  ,
	 {3.91548 , 2.83769 , 1.30904 }  ,
	 {3.82009 , 2.81367 , 2.64041 }  ,
	 {4.65872 , 3.30893 , 2.70943 }  ,
	 {5.19844 , 1.70421 , 2.71916 }  ,
	 {4.20833 , 1.43449 , 2.64335 }  ,
	 {5.27611 , 0.013084 , 2.69422 }  ,
	 {4.18643 , 0.002144 , 2.61595 }  ,
	 {5.3715 , 0.037096 , 1.36285 }  ,
	 {4.28182 , 0.026156 , 1.28458 }  ,
	 {4.30372 , 1.45851 , 1.31199 }  ,
	 {5.29383 , 1.72822 , 1.38779 }  ,
	 {4.75411 , 3.33294 , 1.37806 }  ,
	 {3.79417 , 4.72692 , 1.33442 }  ,
	 {3.69878 , 4.70291 , 2.66579 }  ,
	 {2.39303 , 5.7781 , 2.59163 }  ,
	 {0.842632 , 6.4512 , 2.49269 }  ,
	 {-0.832239 , 6.67002 , 2.37663 }  ,
	 {-0.736848 , 6.69403 , 1.04526 }  ,
	 {0.938022 , 6.47521 , 1.16132 }  ,
	 {2.48842 , 5.80212 , 1.26026 }  ,
	 {5.27806 , -0.792767 , 2.77982 }  ,
	 {5.63252 , 0.102799 , -2.2801 }  ,
	 {5.64158 , -0.701258 , -2.29395 }  ,
	 {-6.61728 , -0.824332 , -3.1745 }  ,
	 {4.34916 , 0.089914 , -2.37228 }  ,
	 {5.43886 , 0.100855 , -2.29401 }  ,
	 {5.34347 , 0.076842 , -0.962631 }  ,
	 {4.25377 , 0.065902 , -1.0409 }  ,
	 {3.52676 , 0.017708 , 1.28071 }  ,
	 {-4.73126 , -0.065199 , 0.687539 }  ,
	 {5.26899 , 0.01129 , 2.79368 }  ,
	 {-6.98988 , -0.111784 , 1.91313 }  ,
	 {-6.72174 , -0.044287 , -1.82927 }  ,
	 {-5.47584 , -0.031779 , -1.73978 }  ,
	 {-5.38045 , -0.007767 , -3.07115 }  ,
	 {-6.62635 , -0.020275 , -3.16065 }  ,
	 {-6.68221 , 1.64801 , -1.79592 }  ,
	 {-6.58682 , 1.67202 , -3.12729 }  ,
	 {-5.43464 , 1.42382 , -3.04922 }  ,
	 {-6.98081 , -0.915841 , 1.89927 }  ,
	 {-4.7222 , -0.869256 , 0.673687 }  ,
	 {-4.54337 , -0.824242 , -1.82219 }  ,
	 {3.71465 , -0.741335 , -1.22902 }  ,
	 {-4.55244 , -0.020184 , -1.80834 }  ,
	 {3.70559 , 0.062722 , -1.21517 }  ,
	 {3.53583 , -0.78635 , 1.26686 }  ,
	 {4.27566 , 1.49825 , -1.0135 }  ,
	 {4.37106 , 1.52226 , -2.34488 }  ,
	 {5.36117 , 1.79198 , -2.26907 }  ,
	 {5.26578 , 1.76796 , -0.937697 }  ,
	 {3.88745 , 2.87743 , -1.01644 }  ,
	 {3.98284 , 2.90144 , -2.34782 }  ,
	 {4.82145 , 3.3967 , -2.2788 }  ,
	 {4.72606 , 3.37269 , -0.947425 }  ,
	 {3.12159 , 4.08791 , -1.04948 }  ,
	 {3.21698 , 4.11193 , -2.38086 }  ,
	 {3.86152 , 4.79068 , -2.32244 }  ,
	 {3.76613 , 4.76667 , -0.991061 }  ,
	 {2.04229 , 5.02829 , -1.10985 }  ,
	 {2.13768 , 5.0523 , -2.44123 }  ,
	 {2.55576 , 5.86587 , -2.3966 }  ,
	 {2.46037 , 5.84186 , -1.06523 }  ,
	 {0.739931 , 5.6198 , -1.1925 }  ,
	 {0.835322 , 5.64381 , -2.52387 }  ,
	 {-0.581 , 5.83691 , -2.62187 }  ,
	 {1.00537 , 6.53897 , -2.49554 }  ,
	 {0.909981 , 6.51495 , -1.16417 }  ,
	 {-0.676391 , 5.8129 , -1.29049 }  ,
	 {-1.99265 , 5.61542 , -2.72701 }  ,
	 {-2.08804 , 5.59141 , -1.39563 }  ,
	 {-3.28137 , 4.9979 , -2.83048 }  ,
	 {-3.37677 , 4.97389 , -1.4991 }  ,
	 {-4.33923 , 4.03607 , -2.92362 }  ,
	 {-4.43462 , 4.01205 , -1.59224 }  ,
	 {-5.17299 , 2.78647 , -1.66725 }  ,
	 {-5.07759 , 2.81048 , -2.99863 }  ,
	 {-6.08342 , 3.28722 , -3.06209 }  ,
	 {-5.53003 , 1.39981 , -1.71784 }  ,
	 {-6.17881 , 3.26321 , -1.73072 }  ,
	 {-5.25053 , 4.67615 , -1.63872 }  ,
	 {-5.15514 , 4.70016 , -2.9701 }  ,
	 {-3.87391 , 5.80132 , -2.85844 }  ,
	 {-2.33906 , 6.50539 , -2.73577 }  ,
	 {-0.669499 , 6.75779 , -2.6116 }  ,
	 {-0.76489 , 6.73378 , -1.28022 }  ,
	 {-2.43445 , 6.48138 , -1.4044 }  ,
	 {-3.9693 , 5.77731 , -1.52707 }
};

const Face bridgeFaces[254] = PROGMEM{
 {0 , 1 , 2 } ,
 {1 , 0 , 3 } ,
 {3 , 0 , 4 } ,
 {4 , 0 , 5 } ,
 {5 , 0 , 6 } ,
 {5 , 6 , 7 } ,
 {6 , 8 , 7 } ,
 {6 , 9 , 8 } ,
 {10 , 9 , 6 } ,
 {9 , 10 , 11 } ,
 {11 , 2 , 10 } ,
 {2 , 11 , 1 } ,
 {1 , 9 , 11 } ,
 {9 , 1 , 3 } ,
 {3 , 8 , 9 } ,
 {8 , 3 , 4 } ,
 {4 , 12 , 8 } ,
 {12 , 4 , 13 } ,
 {4 , 5 , 13 } ,
 {13 , 5 , 14 } ,
 {7 , 14 , 5 } ,
 {14 , 7 , 15 } ,
 {7 , 12 , 15 } ,
 {7 , 8 , 12 } ,
 {15 , 12 , 16 } ,
 {12 , 17 , 16 } ,
 {17 , 12 , 13 } ,
 {13 , 14 , 17 } ,
 {17 , 14 , 18 } ,
 {14 , 19 , 18 } ,
 {19 , 14 , 15 } ,
 {15 , 16 , 19 } ,
 {19 , 16 , 20 } ,
 {16 , 21 , 20 } ,
 {21 , 16 , 17 } ,
 {17 , 18 , 21 } ,
 {21 , 18 , 22 } ,
 {22 , 18 , 23 } ,
 {18 , 24 , 23 } ,
 {24 , 18 , 19 } ,
 {19 , 25 , 24 } ,
 {19 , 20 , 25 } ,
 {20 , 22 , 25 } ,
 {22 , 20 , 21 } ,
 {26 , 25 , 22 } ,
 {25 , 26 , 27 } ,
 {28 , 27 , 26 } ,
 {27 , 28 , 29 } ,
 {30 , 29 , 28 } ,
 {29 , 30 , 31 } ,
 {30 , 32 , 31 } ,
 {32 , 30 , 33 } ,
 {34 , 33 , 30 } ,
 {35 , 33 , 34 } ,
 {35 , 36 , 33 } ,
 {37 , 36 , 35 } ,
 {36 , 37 , 38 } ,
 {38 , 39 , 37 } ,
 {39 , 38 , 40 } ,
 {40 , 36 , 38 } ,
 {36 , 40 , 41 } ,
 {39 , 41 , 40 } ,
 {41 , 39 , 42 } ,
 {37 , 42 , 39 } ,
 {42 , 37 , 35 } ,
 {35 , 43 , 42 } ,
 {43 , 35 , 34 } ,
 {34 , 44 , 43 } ,
 {44 , 34 , 45 } ,
 {34 , 30 , 45 } ,
 {45 , 30 , 28 } ,
 {45 , 28 , 46 } ,
 {46 , 28 , 26 } ,
 {46 , 26 , 22 } ,
 {46 , 22 , 47 } ,
 {47 , 22 , 23 } ,
 {47 , 23 , 48 } ,
 {23 , 49 , 48 } ,
 {49 , 23 , 24 } ,
 {24 , 50 , 49 } ,
 {25 , 50 , 24 } ,
 {25 , 51 , 50 } ,
 {27 , 51 , 25 } ,
 {29 , 51 , 27 } ,
 {29 , 44 , 51 } ,
 {31 , 44 , 29 } ,
 {31 , 43 , 44 } ,
 {32 , 43 , 31 } ,
 {32 , 42 , 43 } ,
 {41 , 42 , 32 } ,
 {33 , 41 , 32 } ,
 {41 , 33 , 36 } ,
 {44 , 46 , 51 } ,
 {46 , 44 , 45 } ,
 {47 , 51 , 46 } ,
 {51 , 47 , 50 } ,
 {48 , 50 , 47 } ,
 {50 , 48 , 49 } ,
 {39 , 52 , 37 } ,
 {53 , 52 , 39 } ,
 {52 , 53 , 54 } ,
 {53 , 55 , 54 } ,
 {55 , 53 , 56 } ,
 {56 , 53 , 57 } ,
 {53 , 58 , 57 } ,
 {39 , 58 , 53 } ,
 {40 , 58 , 39 } ,
 {58 , 40 , 59 } ,
 {38 , 59 , 40 } ,
 {38 , 60 , 59 } ,
 {38 , 61 , 60 } ,
 {38 , 1 , 61 } ,
 {62 , 1 , 38 } ,
 {62 , 2 , 1 } ,
 {63 , 2 , 62 } ,
 {2 , 63 , 10 } ,
 {64 , 10 , 63 } ,
 {10 , 64 , 65 } ,
 {64 , 66 , 65 } ,
 {66 , 64 , 67 } ,
 {67 , 68 , 64 } ,
 {68 , 67 , 69 } ,
 {67 , 70 , 69 } ,
 {70 , 67 , 66 } ,
 {67 , 56 , 66 } ,
 {56 , 67 , 55 } ,
 {64 , 55 , 67 } ,
 {55 , 64 , 71 } ,
 {71 , 64 , 63 } ,
 {63 , 52 , 71 } ,
 {52 , 63 , 62 } ,
 {37 , 52 , 62 } ,
 {62 , 38 , 37 } ,
 {72 , 71 , 52 } ,
 {71 , 72 , 55 } ,
 {73 , 55 , 72 } ,
 {55 , 73 , 54 } ,
 {54 , 73 , 74 } ,
 {75 , 74 , 73 } ,
 {74 , 75 , 76 } ,
 {75 , 56 , 76 } ,
 {75 , 66 , 56 } ,
 {66 , 75 , 65 } ,
 {65 , 75 , 11 } ,
 {11 , 75 , 1 } ,
 {61 , 1 , 75 } ,
 {75 , 72 , 61 } ,
 {72 , 75 , 73 } ,
 {72 , 60 , 61 } ,
 {60 , 72 , 77 } ,
 {72 , 52 , 77 } ,
 {77 , 52 , 74 } ,
 {54 , 74 , 52 } ,
 {74 , 60 , 77 } ,
 {60 , 74 , 76 } ,
 {76 , 56 , 60 } ,
 {59 , 60 , 56 } ,
 {56 , 78 , 59 } ,
 {78 , 56 , 79 } ,
 {57 , 79 , 56 } ,
 {79 , 57 , 80 } ,
 {58 , 80 , 57 } ,
 {80 , 58 , 81 } ,
 {58 , 78 , 81 } ,
 {78 , 58 , 59 } ,
 {59 , 57 , 58 } ,
 {57 , 59 , 56 } ,
 {81 , 78 , 82 } ,
 {79 , 82 , 78 } ,
 {82 , 79 , 83 } ,
 {79 , 80 , 83 } ,
 {83 , 80 , 84 } ,
 {81 , 84 , 80 } ,
 {84 , 81 , 85 } ,
 {81 , 82 , 85 } ,
 {85 , 82 , 86 } ,
 {83 , 86 , 82 } ,
 {86 , 83 , 87 } ,
 {83 , 84 , 87 } ,
 {87 , 84 , 88 } ,
 {85 , 88 , 84 } ,
 {88 , 85 , 89 } ,
 {85 , 86 , 89 } ,
 {89 , 86 , 90 } ,
 {86 , 91 , 90 } ,
 {91 , 86 , 87 } ,
 {87 , 88 , 91 } ,
 {91 , 88 , 92 } ,
 {88 , 93 , 92 } ,
 {93 , 88 , 89 } ,
 {89 , 90 , 93 } ,
 {93 , 90 , 94 } ,
 {90 , 95 , 94 } ,
 {95 , 90 , 91 } ,
 {91 , 92 , 95 } ,
 {95 , 92 , 96 } ,
 {96 , 92 , 97 } ,
 {92 , 98 , 97 } ,
 {98 , 92 , 93 } ,
 {93 , 99 , 98 } ,
 {93 , 94 , 99 } ,
 {94 , 96 , 99 } ,
 {96 , 94 , 95 } ,
 {100 , 99 , 96 } ,
 {99 , 100 , 101 } ,
 {102 , 101 , 100 } ,
 {101 , 102 , 103 } ,
 {104 , 103 , 102 } ,
 {103 , 104 , 105 } ,
 {104 , 106 , 105 } ,
 {106 , 104 , 107 } ,
 {108 , 107 , 104 } ,
 {69 , 107 , 108 } ,
 {69 , 70 , 107 } ,
 {109 , 107 , 70 } ,
 {107 , 109 , 106 } ,
 {109 , 68 , 106 } ,
 {65 , 68 , 109 } ,
 {68 , 65 , 64 } ,
 {70 , 65 , 109 } ,
 {65 , 70 , 66 } ,
 {106 , 68 , 110 } ,
 {69 , 110 , 68 } ,
 {110 , 69 , 108 } ,
 {108 , 111 , 110 } ,
 {111 , 108 , 112 } ,
 {108 , 104 , 112 } ,
 {112 , 104 , 102 } ,
 {112 , 102 , 113 } ,
 {113 , 102 , 100 } ,
 {113 , 100 , 96 } ,
 {113 , 96 , 114 } ,
 {96 , 97 , 114 } ,
 {114 , 97 , 115 } ,
 {97 , 116 , 115 } ,
 {116 , 97 , 98 } ,
 {98 , 117 , 116 } ,
 {98 , 99 , 117 } ,
 {99 , 118 , 117 } ,
 {101 , 118 , 99 } ,
 {103 , 118 , 101 } ,
 {103 , 111 , 118 } ,
 {105 , 111 , 103 } ,
 {105 , 110 , 111 } ,
 {106 , 110 , 105 } ,
 {111 , 113 , 118 } ,
 {113 , 111 , 112 } ,
 {114 , 118 , 113 } ,
 {118 , 114 , 117 } ,
 {115 , 117 , 114 } ,
 {117 , 115 , 116 } ,
 {10 , 65 , 11 } ,
 {10 , 0 , 2 } ,
 {0 , 10 , 6 } };
