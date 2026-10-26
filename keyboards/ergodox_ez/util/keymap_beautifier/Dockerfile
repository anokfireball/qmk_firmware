FROM python:3.8.3-alpine3.10@sha256:152b1952d4b42e360f2efd3037df9b645328c0cc6fbe9c63decbffbff407b96a

WORKDIR /usr/src/app
COPY requirements.txt ./
RUN pip install --no-cache-dir -r requirements.txt
COPY ./KeymapBeautifier.py ./KeymapBeautifier.py

CMD [ "python", "./KeymapBeautifier.py", "-h" ]
