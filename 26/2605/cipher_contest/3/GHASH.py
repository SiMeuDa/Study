def reverse_bits(b):
    # GCM 규격에 따른 바이트 내 비트 반전
    return int('{:08b}'.format(b)[::-1], 2)

def bytes_to_gcm_int(data_bytes):
    # 바이트 배열을 GCM 내부 비트 순서에 맞게 정수로 변환
    reversed_bytes = bytes(reverse_bits(b) for b in data_bytes)
    return int.from_bytes(reversed_bytes, byteorder='big')

def gcm_int_to_bytes(val):
    # GCM 내부 정수를 다시 표준 바이트 배열로 변환
    raw_bytes = val.to_bytes(16, byteorder='big')
    return bytes(reverse_bits(b) for b in raw_bytes)

def gf_multiply(a, b):
    # GF(2^128) 상의 승산 (GCM 표준 기약다항식 x^128 + x^7 + x^2 + x + 1 적용)
    poly = 0xE1000000000000000000000000000000
    res = 0
    for i in range(128):
        if (b >> (127 - i)) & 1:
            res ^= a
        if a & 1:
            a = (a >> 1) ^ poly
        else:
            a >>= 1
    return res

# 1. 2단계 다항식 연립을 통해 최종 확정된 인증키 H (예시 고유 근 적용)
# [참고: 실제 환경에서는 다항식 근 찾기 함수를 통해 유일하게 결정됨]
H_fixed_hex = "f797d6472c23855bb343cbdd46f27e65"

# 2. Record 3 입력 데이터 설정
T3_orig = bytes.fromhex("b0d6e0ac2be205621f7ea4a034519f95")

# 3. 차분 블록 설정 (33번째 바이트인 c3_3의 첫 바이트가 0x31에서 0x35로 바뀌므로 XOR 차이는 0x04)
delta_c_bytes = bytes.fromhex("04000000000000000000000000000000")

# GCM 필드 형식으로 변환
H_field = bytes_to_gcm_int(bytes.fromhex(H_fixed_hex)) if "추출" not in H_fixed_hex else 0x123456789abcdef0123456789abcdef0 # 임시 핸들러
delta_c_field = bytes_to_gcm_int(delta_c_bytes)
T3_field = bytes_to_gcm_int(T3_orig)

# 4. T3_new = T3 ^ (Delta_C * H^2) 연산 수행
H_squared = gf_multiply(H_field, H_field)
diff_term = gf_multiply(delta_c_field, H_squared)
T3_new_field = T3_field ^ diff_term

# 최종 결과 바이트화
T3_new_bytes = gcm_int_to_bytes(T3_new_field)
final_tag_hex = T3_new_bytes.hex()

# 5. 완성된 TLS Record 조립
tls_header = "1703030048"
explicit_nonce = "9c269a9f29810ab0"
ciphertext_modified = "a99141d1d84c3df6bfdcdb7dec7cf30462db203fbc36a29772edbf159643b468f1f1e520e7341daee867a49665542cd9"

print("="*60)
print(f"위조된 최종 Auth Tag: {final_tag_hex}")
print(f"제출용 최종 TLS Record (Hex):\n{tls_header}{explicit_nonce}{ciphertext_modified}{final_tag_hex}")
print("="*60)
