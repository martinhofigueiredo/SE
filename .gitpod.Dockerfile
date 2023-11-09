FROM gitpod/workspace-full

USER gitpod

ENV PIP_USER=false
ENV PLATFORMIO_PENV_DIR=/home/gitpod/.platformio
ENV PATH="${PLATFORMIO_PENV_DIR}/bin:${PATH}"
RUN python3 -c "$(curl -fsSL https://raw.githubusercontent.com/platformio/platformio/master/scripts/get-platformio.py)"
