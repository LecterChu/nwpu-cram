import os
import zipfile

_A1_FILES = [
    "pytorch101.py",
    "pytorch101.ipynb",
    "knn.py",
    "knn.ipynb",
]

_A2_FILES = [
    "linear_classifier.py",
    "linear_classifier.ipynb",
    "two_layer_net.py",
    "two_layer_net.ipynb",
    "svm_best_model.pt",
    "softmax_best_model.pt",
    "nn_best_model.pt",
]

_A3_FILES = [
    "fully_connected_networks.py",
    "fully_connected_networks.ipynb",
    "convolutional_networks.py",
    "convolutional_networks.ipynb",
    "best_overfit_five_layer_net.pth",
    "best_two_layer_net.pth",
    "one_minute_deepconvnet.pth",
    "overfit_deepconvnet.pth",
]


def make_a1_submission(assignment_path, uniquename=None, umid=None):
    _make_submission(assignment_path, _A1_FILES, "A1", uniquename, umid)


def make_a2_submission(assignment_path, uniquename=None, umid=None):
    _make_submission(assignment_path, _A2_FILES, "A2", uniquename, umid)


def make_a3_submission(assignment_path, uniquename=None, umid=None):
    _make_submission(assignment_path, _A3_FILES, "A3", uniquename, umid)


def _make_submission(
    assignment_path, file_list, assignment_no, uniquename=None, umid=None
):
    if uniquename is None or umid is None:
        uniquename, umid = _get_user_info()
    zip_path = "{}_{}_{}.zip".format(uniquename, umid, assignment_no)
    zip_path = os.path.join(assignment_path, zip_path)
    print("Writing zip file to: ", zip_path)
    with zipfile.ZipFile(zip_path, "w") as zf:
        for filename in file_list:
            in_path = os.path.join(assignment_path, filename)
            if not os.path.isfile(in_path):
                raise ValueError('Could not find file "%s"' % filename)
            zf.write(in_path, filename)


def _get_user_info():
    if uniquename is None:
        uniquename = input("Enter your uniquename (e.g. justincj): ")
    if umid is None:
        umid = input("Enter your umid (e.g. 12345678): ")
    return uniquename, umid
