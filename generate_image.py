from PIL import Image, ImageDraw, ImageFont

# 텍스트 내용
text_content = """
강의 개요
디지털영상신호처리에 대한 기초이론을 이해하고 이를 확장하여 인공지능에 활용할 수 있는 지능형 영상처리 응용분야를 학습한다. 이를 바탕으로 개별적인 실습/토론/과제를 통해서 영상 데이터 분석을 기반으로 응용가능한 실무 프로젝트를 진행한다.

<교과목 목표>
디지털영상신호처리의 특성을 이해하고 실제 인공지능 응용분야의 다양한 기술에 적용하기 위한 기초 기술들을 습득한다. 이를 바탕으로 개별적인 실습/토론/과제를 통해 영상 데이터 분석 기술에 대한 이해를 높이고 실무 프로젝트를 통해서 실무 현장에서 수행되는 과업들을 간접 경험해본다.
"""

# 이미지 생성
image_width = 1200
image_height = 400
background_color = "white"
image = Image.new("RGB", (image_width, image_height), background_color)

# 텍스트 그리기 준비
draw = ImageDraw.Draw(image)
font_size = 20

try:
    font = ImageFont.truetype("arial.ttf", font_size)
except IOError:
    font = ImageFont.load_default()

text_color = "black"
padding = 20

# 텍스트 위치 계산 및 그리기
text_x = padding
text_y = padding
draw.multiline_text((text_x, text_y), text_content, fill=text_color, font=font, align="left")

# 이미지 저장
output_file = "lecture_overview.png"
image.save(output_file)
print(f"Image saved as {output_file}")
