struct FragmentOut {
    float4 outColor [[color(0)]];
};

fragment struct FragmentOut testMatrices() {
    //Initialization
    float4x4 matrix1 = float4x4(float4(1.0, 2.0, 3.0, 4.0),
                                float4(5.0, 6.0, 7.0, 8.0),
                                float4(9.0, 10.0, 11.0, 12.0),
                                float4(13.0, 14.0, 15.0, 16.0));
    float4x4 matrix2 = float4x4(1.0);
    
    //Multiplication

    struct FragmentOut fragmentOut;
    fragmentOut.outColor = float4(0.0, 0.0, 0.0, 1.0);//matrix1[0];

    return fragmentOut;
}
