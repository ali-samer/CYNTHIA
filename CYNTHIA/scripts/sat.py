# Python script to import satellite images for cpp app
import requests
from PIL import Image
from io import BytesIO

def get_landsat_image(params):

    api_endpoint = "https://api.nasa.gov/planetary/earth/imagery"

    response = requests.get(api_endpoint, params=params)

    img = Image.open(BytesIO(response.content))

    return img