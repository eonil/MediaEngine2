





vec3
rotate_vector_by_quaternion(vec4 quat, vec3 vec)
{
	return vec + 2.0 * cross(cross(vec, quat.xyz) + quat.w * vec, quat.xyz);
}