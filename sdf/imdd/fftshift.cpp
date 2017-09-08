//-- Does 1D fftshift 
template<typename T>
inline void fftshift1D(T *in, T *out, int ydim)
{
 int pivot = (ydim % 2 == 0) ? (ydim / 2) : ((ydim - 1) / 2);
 int rightHalf = ydim-pivot;
 int leftHalf = pivot;
 memcpy(out, in+(pivot), sizeof(T)*rightHalf);
 memcpy(out+rightHalf, in, sizeof(T)*leftHalf);
}

