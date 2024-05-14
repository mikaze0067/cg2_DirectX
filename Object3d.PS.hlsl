float4 main() : SV_TARGET
{
	return float4(1.0f, 1.0f, 1.0f, 1.0f);
}
struct PixeleShaderOutput{
    float4 color : SV_TARGET;
};

PixeleShaderOutput main(){
    PixeleShaderOutput output;
    output.color = float4(1.0, 1.0, 1.0, 1.0);
    return output;
}